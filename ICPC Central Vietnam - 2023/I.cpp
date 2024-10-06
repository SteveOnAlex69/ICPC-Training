#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1LL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
#define block_of_code if(true)
 
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
ll gcd(ll a, ll b){return __gcd(a, b);}
 
int pop_cnt(ll mask){return __builtin_popcountll(mask);}
int ctz(ull mask){return __builtin_ctzll(mask);}
int logOf(ull mask){return 63 - __builtin_clzll(mask);}
ll LASTBIT(ll mask){return (mask) & (-mask);}
ll FIRSTBIT(ll mask){return MASK(logOf(mask));}
 
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return l + (ull) rng() % (r - l + 1);}
 
template <class T1, class T2>
    bool maximize(T1 &a, T2 b){
        if (a < b) {a = b; return true;}
        return false;
    }
 
template <class T1, class T2>
    bool minimize(T1 &a, T2 b){
        if (a > b) {a = b; return true;}
        return false;
    }
 
template <class T>
    void printArr(T container, string separator = " ", string finish = "\n", ostream &out = cout){
        for(auto item: container) out << item << separator;
        out << finish;
    }
 
template <class T>
    void remove_dup(vector<T> &a){
        sort(ALL(a));
        a.resize(unique(ALL(a)) - a.begin());
    }

struct DSU{
    int n;
    vector<int> parent, sz;

    DSU(int _n){
        n = _n;
        parent.resize(n); sz.resize(n, 1);
        for(int i = 1; i<n; ++i) parent[i] = i;
    }

    int find_set(int u){return (u == parent[u]) ? u : (parent[u] = find_set(parent[u]));}
    bool same_set(int u, int v){return find_set(u) == find_set(v);}

    bool join_set(int u, int v){
        u = find_set(u), v = find_set(v);
        if (u != v){
            if (sz[u] < sz[v]) swap(u, v);
            parent[v] = u;
            sz[u] += sz[v];
            return true;
        }
        return false;
    }

    int get_size(int u){return sz[find_set(u)];}
};

const int N = 505;
int x, y;
string s[N];
ll ans = 0;

int convert(int i, int j){
    return i * y + j;
}

namespace GraphPart{
    const int N = 250000 + 69;
    int n, m;
    bool activated[N];
    vector<int> graph[N], dfs_tree[N];
     
    int num[N], low[N];
    bool isJoint[N];
    vector<int> st;
    int dfs_cnt;
    vector<vector<int>> bbc;
     
    void tarjan(int u, int p){
        num[u] = low[u] = ++dfs_cnt;
     
        vector<int> child;
        for(int v: graph[u]) {
            if (v == p) {p = -1; continue;}
            if (num[v]){
                minimize(low[u], num[v]);
            }
            else{
                child.push_back(v);
                tarjan(v, u);
                minimize(low[u], low[v]);
                if (low[v] >= num[u]){
                    isJoint[u] = true;
                }
            }
        }
        if (u == p) isJoint[u] = isJoint[u] && (child.size() >= 2);
        for(int v: child){
            if (isJoint[u] && low[v] >= num[u]) dfs_tree[u].push_back(-v);
            else dfs_tree[u].push_back(v);
        }
    }
     
    void get_block(int u){
        st.push_back(u);
        for(int v: dfs_tree[u]){
            get_block(abs(v));
            if (v < 0){
                bbc.push_back({});
                while(bbc.back().empty() || bbc.back().back() != abs(v)){
                    bbc.back().push_back(st.back());
                    st.pop_back();
                }
                bbc.back().push_back(u);
            }
        }
    }
     
    vector<int> bc_tree[2*N];
    int joint_cnt = 0;
    int pos[2*N];
    int sz[2 * N], og[2 * N];
     
    int generate_block_cut_tree(){
        dfs_cnt = 0;
        for(int i= 0; i<n; ++i) if (num[i] == 0 && activated[i]){
            tarjan(i, i);
            get_block(i);
            if (st.size()) {
                bbc.push_back(st);
                st.clear();
            }
        }
     
        int idx = 0;
        for(int i= 0; i<n; ++i) if (activated[i]) {
            if (!isJoint[i]) continue;
            joint_cnt++;
            pos[i] = ++idx;
            sz[idx] = 1;
        }
     
        for(vector<int> i: bbc){
            ++idx;
            sz[idx] = i.size();
            for(int j: i){
                if (isJoint[j]){
                    int u = idx, v = pos[j];
                    sz[v]--;
                    bc_tree[u].push_back(v);
                    bc_tree[v].push_back(u);
                }
            }
        }
        for(int i= 1; i<=idx; ++i) og[i] = sz[i];
        return idx;
    }

    bool visited[N * 2];

    void find_sz(int u, int p){
        visited[u] = true;
        for(int v: bc_tree[u]) if (v != p){
            find_sz(v, u);
            sz[u] += sz[v];
        }
    }

    void dfs(int u, int p, int big){
        for(int v: bc_tree[u]) if (v != p){
            dfs(v, u, big);
            if (og[u] > 0){
                ans += 1LL * (og[u] - 1) * sz[v];
            }
        }
        if (og[u] > 0){
            int other = big - sz[u];
            ans += 1LL * (og[u] - 1) * other;
        }
    }

    void solve(){
        n = x * y;
        for(int i = 0; i<x; ++i) for(int j= 0; j<y; ++j) if (s[i][j] == '.'){
            int idx = convert(i, j);
            activated[idx] = true;
            if (i + 1 < x && s[i+1][j] == '.') {
                graph[idx].push_back(idx + y);
                graph[idx + y].push_back(idx);
                m++;
            }
            if (j + 1 < y && s[i][j+1] == '.') {
                graph[idx].push_back(idx + 1);
                graph[idx + 1].push_back(idx);
                m++;
            }
        }

        int tot_vertices = generate_block_cut_tree();

        for(int i = 1; i <= tot_vertices; ++i) if (sz[i] > 0 && !visited[i]){
            find_sz(i, 0);
            int big = sz[i];
            dfs(i, 0, big);
        }
    }
}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    clock_t start = clock();

    cin >> x >> y;
    for(int i = 0; i<x; ++i) cin >> s[i];

    DSU mst(x * y);
    int cnt = 0;
    for(int i = 0; i<x; ++i) for(int j= 0; j<y; ++j) if (s[i][j] == '.'){
        cnt++;
        if (i + 1 < x && s[i+1][j] == '.') 
            mst.join_set(convert(i, j), convert(i + 1, j));
        if (j + 1 < y && s[i][j+1] == '.') 
            mst.join_set(convert(i, j), convert(i, j + 1));
    }

    for(int i = 0; i < x * y; ++i) if (s[i / y][i % y] == '.' && mst.find_set(i) == i){
        ans += 1LL * mst.get_size(i) * (cnt - mst.get_size(i));
    }

    GraphPart::solve();
    // ans /= 2;

    cout << ans << "\n";

    cerr << "Time elapsed: " << clock() - start << " ms!\n";
    return 0;
}

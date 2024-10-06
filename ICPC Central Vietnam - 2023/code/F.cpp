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

#define fi first 
#define se second

const int MAX = 1e5 + 10, LOG = 17;

int N;
vector<pair<int, int>> adj[MAX];
array<int, 4> edges[MAX];
int d[MAX][LOG], h[MAX], in[MAX], out[MAX], timer, idEdge[MAX], cnt[MAX];

void dfs(int u, int p = -1){
    in[u] = ++timer;
    for(auto o: adj[u]){
        int v = o.fi;
        int id = o.se;
        if(v == p) continue;
        idEdge[v] = id;
        h[v] = h[u] + 1;
        d[v][0] = u;
        for(int i = 1; i < LOG; i++){
            d[v][i] = d[d[v][i - 1]][i - 1];
        }
        dfs(v, u);
    }
    out[u] = timer;
}

int lca(int u, int v){
    if(h[u] < h[v]) swap(u, v);
    int delta = h[u] - h[v];
    for(int i = 0; i < LOG; i++) if((delta >> i) & 1){
        u = d[u][i];
    }
    if(u == v) return u;
    for(int i = LOG - 1; i >= 0; i--) if(d[u][i] != d[v][i]){
        u = d[u][i];
        v = d[v][i];
    }
    return d[u][0];
}

void solve(){
    cin >> N;
    for(int i = 1; i < N; i++){
        int u, v, c1, c2; cin >> u >> v >> c1 >> c2;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        edges[i] = {u, v, c1, c2};
    }
    dfs(1);
    for(int i = 1; i < N; i++){
        cnt[in[i]]++;
        cnt[in[i + 1]]++;
        cnt[in[lca(i, i + 1)]] -= 2;
    }
    for(int i = 1; i <= N; i++){
        cnt[i] += cnt[i - 1];
    }
    ll ans = 0;
    for(int i = 2; i <= N; i++){
        int c = cnt[out[i]] - cnt[in[i] - 1];
        int id = idEdge[i];
        ans += min(1LL * edges[id][3], 1LL * edges[id][2] * c);
    }
    cout << ans << '\n';
}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    clock_t start = clock();


    solve();

    cerr << "Time elapsed: " << clock() - start << " ms!\n";
    return 0;
}

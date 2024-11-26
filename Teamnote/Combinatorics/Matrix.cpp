/*
    Problem: A

Sech Phan Hai Minh live footage 
        |
        |
        v

⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⠿⣿⢿⣿⡟⠛⠷⡀⠀⠀⠀⠀⠀⢀⣠⣤⣤⣤⣀⣀⣀⣀⠀⠀⠀⠀
⠀⢰⣿⣿⣿⡿⣿⣿⡛⠅⠁⠈⠈⠘⠳⠀⠀⢒⠀⠀⠀⡠⠊⠉⠉⣽⣿⣿⣿⣿⣿⣿⣿⣦⡀⠀
⠀⢸⣿⣿⣿⣿⡀⠀⣰⢤⡀⠀⠀⠀⠀⠀⠀⠾⠀⠀⡜⠀⠀⠀⠀⠛⠻⣿⢿⣿⣿⣿⣿⣿⣿⡆
⠀⠈⣿⣿⣿⠟⠋⣿⢌⣿⡷⢄⠀⠀⠀⢀⣠⣾⠀⣸⣿⡏⢡⠀⠀⠀⠀⠀⠊⢛⣿⣿⣿⣿⣿⣿
⠀⠀⣿⣿⣿⣿⣾⣿⣿⢿⡄⠀⡀⠀⠀⠙⢿⡯⢀⡻⢿⡿⠛⠁⠀⠀⠀⠀⠀⣻⣹⣿⣿⣿⣿⣿
⠀⢀⣿⣷⡛⢿⣿⣿⣷⣿⡍⠀⠷⣦⢄⣀⣼⡇⢫⣰⠆⠀⠀⡀⠀⠀⠀⠀⣴⣓⣺⣿⣿⣿⣿⡟
⣀⣼⣧⡌⠳⣤⠿⣿⡿⣿⣶⣤⣴⣿⣿⣯⣿⣿⣿⣧⡀⠀⠸⡕⠀⠀⠀⠀⣿⠿⠁⠘⣿⣿⡟⠀
⣩⡵⢤⠟⢄⠘⢤⡘⢇⠘⣿⣿⣿⣿⣿⣿⣿⣿⣥⣎⠁⠀⠀⢒⣠⣦⣦⣴⡇⠀⠀⣬⣿⣿⠃⠀
⠸⣷⣟⠱⡀⠳⢤⡀⠀⠳⣽⣿⣿⣿⣿⣿⡿⠻⢿⣿⣇⢀⣀⣴⣿⣿⣿⣿⡇⠀⠀⣿⣿⣯⣲⠀
⢷⢌⣿⡆⣉⠀⠀⠀⠀⠀⣸⡏⠙⠛⠿⠿⠃⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⢠⣿⡷⡳⠃⠀
⡙⢿⣿⣿⡿⣦⣤⠄⠀⢸⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠁⠀⢻⣿⣿⣿⣆⣤⣾⣯⠞⠁⠀⠀
⠈⢦⡹⣾⣿⣾⡟⠛⠀⠀⢺⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⠟⠁⠀⠀⠀⠀⠀
⣅⣨⡟⠻⣿⣿⣿⡆⠀⢤⡄⢷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣩⢟⠕⠀⠀⠀⠀⠀⠀⠀
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int ul;
typedef unsigned long long ull;

#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

ll gcd(ll a, ll b){return __gcd(a, b);}
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}

ll LASTBIT(ll mask){return (mask) & (-mask);}
int pop_cnt(ll mask){return __builtin_popcountll(mask);}
int ctz(ull mask){return __builtin_ctzll(mask);}
int logOf(ull mask){return 63 - __builtin_clzll(mask);}

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
    void printArr(T the_array_itself, string separator = " ", string finish = "\n", ostream &out = cout){
        for(auto item: the_array_itself) out << item << separator;
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
        parent.resize(n+1); sz.resize(n+1, 1);
        for(int i = 1; i<=n; ++i) parent[i] = i;
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

int di(int n, int k){
    return (n / k) + (n % k > 0);
}

int n; 

vector<int> knapknap(vector<int> a){
    int m = a.size();
    bool dp[m + 1][n + 1]; memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for(int i = 0; i < m; ++i) for(int j = 0; j <= n; ++j) if (dp[i][j]){
        dp[i+1][j] = 1;
        dp[i+1][j + a[i]] = 1;
    }

    int L = n - di(n * 3, 4);
    int idx = -1;
    for(int i = L; i <= n; ++i) if (dp[m][i]){
        idx = i;
        break;
    }

    vector<int> ans;
    for(int i = m-1; i >= 0; --i){
        if (dp[i][idx]) continue;
        idx -= a[i];
        ans.push_back(i);
    }

    return ans;
}

void solve(){
    cin >> n;
    vector<string> grid(n);
    for(int i = 0; i<n; ++i) cin >> grid[i];

    int cnt0 = 0, cnt1 = 0;
    for(int i = 0; i<n; ++i) for(int j = 0; j<n; ++j) if (grid[i][j] == 'F') cnt0++;
        else if (grid[i][j] == 'S') cnt1++;

    bool flipped = false;
    if (cnt0 < cnt1){
        flipped = true;
        swap(cnt0, cnt1);
        for(int i = 0; i < n; ++i) for(int j = 0; j< n; ++j) if (grid[i][j] == 'F') grid[i][j] = 'S';
            else if (grid[i][j] == 'S') grid[i][j] = 'F';
    }

    DSU mst(n);
    for(int i = 0; i<n; ++i) for(int j = 0; j<n; ++j) if (grid[i][j] == 'F') {
        mst.join_set(i, j);
    }

    vector<vector<int>> cc(n);
    for(int i = 0; i < n; ++i) cc[mst.find_set(i)].push_back(i);

    sort(ALL(cc), [](vector<int> a, vector<int> b){return a.size() > b.size();});   
    while(cc.back().empty()) cc.pop_back();

    vector<int> sz;
    for(auto i: cc) sz.push_back(i.size());
    vector<int> chosen_one = knapknap(sz);

    vector<int> black_vertex(n);
    for(int i: chosen_one) for(int j: cc[i]) black_vertex[j] = 1;
    for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) if (grid[i][j] == '?'){
        if (black_vertex[i] != black_vertex[j]) grid[i][j] = 'S';
        else grid[i][j] = 'F';
    }

    if (flipped){
        for(int i = 0; i < n; ++i) for(int j = 0; j< n; ++j) if (grid[i][j] == 'F') grid[i][j] = 'S';
        else if (grid[i][j] == 'S') grid[i][j] = 'F';

    }

    cout << "\n";
    for(int i = 0; i < n; ++i) cout << grid[i] << "\n";

}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    clock_t start = clock();

    solve();    

    cerr << "Time elapsed: " << clock() - start << " ms!\n";

    return 0;
}
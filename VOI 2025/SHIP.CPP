#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
 
template <class T1, class T2>
    bool maximize(T1 &a, T2 b){
        if (a < b) {a = b; return true;}
        return false;
    }

const int N = 2e5 + 69, LOG_N = 18;
const ll INF = 1e18 + 69;
int n;
vector<int> graph[N];
int w[N];
int h[N], parent[N][LOG_N], max_path[N][LOG_N];

void dfs(int u, int p){
    h[u] = h[p] + 1;
    for(int j = 1; MASK(j) < h[u]; ++j){
        int prev = parent[u][j-1];
        parent[u][j] = parent[prev][j-1];
        max_path[u][j] = max(max_path[u][j-1], max_path[prev][j-1]);
    }
    for(int v: graph[u]) if (v != p){
        parent[v][0] = u;
        max_path[v][0] = max(w[u], w[v]);
        dfs(v, u);
    }
}

int get_max_path(int u, int v){
    if (u == v) return w[u];
    if (h[u] < h[v]) swap(u, v);
    int diff = h[u] - h[v];
    int ans = 0;
    for(int j = 0; j< LOG_N; ++j) if (GETBIT(diff, j)){
        maximize(ans, max_path[u][j]);
        u = parent[u][j];
    }
    if (u == v) return ans;
    for(int j = LOG_N - 1; j >= 0; --j) if (parent[u][j] != parent[v][j]){
        maximize(ans, max(max_path[u][j], max_path[v][j]));
        u = parent[u][j];
        v = parent[v][j];
    }
    maximize(ans, max(max_path[u][0], max_path[v][0]));
    return ans;
}

void solve(){
    cin >> n;
    for(int i = 1; i<= n; ++i) cin >> w[i];
    for(int i = 1; i < n; ++i){
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, 0);

    int q; cin >> q;
    vector<ll> dp(n+1, -INF);
    dp[1] = 0;

    while(q--){
        int u, v; cin >> u >> v;
        maximize(dp[v], dp[u] + get_max_path(u, v));
    }

    cout << *max_element(ALL(dp)) << "\n";
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

    freopen("SHIP.INP", "r", stdin);
    freopen("SHIP.OUT", "w", stdout);

    clock_t start = clock();

    solve();

    cerr << "Time elapsed: " << clock() - start << " ms\n";
    return 0;
}
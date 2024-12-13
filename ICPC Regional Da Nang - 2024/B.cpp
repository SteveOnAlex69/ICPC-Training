#include <bits/stdc++.h>
#define MASK(k) (1LL << (k))
#define BIT(x, i) (((x) >> (i)) & 1)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return (ull) rng() % (r - l + 1) + l;}

template <class T1, class T2>
    bool maximize(T1 &a, T2 b){
        if (a < b){a = b; return true;}
        return false;
    }
template <class T1, class T2>
    bool minimize(T1 &a, T2 b){
        if (a > b){a = b; return true;}
        return false;
    }

const ll MOD = 998244353;
const ll INF = 1e9;

const int MAX = 20;

int N, K, M;
int d[MAX][MAX];
pair<int, int> queries[MAX];
int f[MASK(19) + 10][20], trace[MASK(19) + 10][20];
array<int, 3> g[MASK(15) + 10];
int dp[MASK(15) + 10], trace_dp[MASK(15) + 10];
vector<vector<int>> save;

void truyvet(int mask, int i){
    vector<int> path;
    while(true){
        path.push_back(i);
        int j = trace[mask][i];
        mask = mask ^ MASK(i);
        i = j;
        if(mask == 0) break;
    }
    save.push_back(path);
}

void reset(){
    save.clear();
    for(int i = 0; i < MASK(N); i++){
        memset(f[i], 0x3f, sizeof f[i]);
        memset(trace[i], 0, sizeof trace[i]);
    }
    for(int i = 0; i < MASK(M); i++){
        g[i] = {INF, 0, 0};
        dp[i] = INF;
        trace_dp[i] = 0;
    }
}

void solve(){
    cin >> N >> K >> M;
    reset();
    for(int i = 1; i < N; i++){
        for(int j = i + 1; j <= N; j++){
            int x; cin >> x;
            d[i - 1][j - 1] = d[j - 1][i - 1] = x;
        }
    }

    for(int i = 0; i < M; i++){
        int u, v; cin >> u >> v;
        u--;
        v--;
        queries[i] = {u, v};
    }

    for(int i = 0; i < N; i++){
        f[MASK(i)][i] = 0;
    }

    for(int mask = 1; mask < MASK(N); mask++){
        for(int t = mask; t > 0; t -= t & -t){
            int i = __builtin_ctz(t);
            if(f[mask][i] >= (int)1e9) continue;
            for(int t2 = (MASK(N) - 1) ^ mask; t2 > 0; t2 -= t2 & -t2){
                int j = __builtin_ctz(t2);

                if(minimize(f[mask | MASK(j)][j], f[mask][i] + d[i][j])){
                    trace[mask | MASK(j)][j] = i;
                }
            }
        }
    }

    for(int mask = 0; mask < MASK(M); mask++){
        g[mask] = {INF, 0, 0};
    }

    for(int mask = MASK(N) - 1; mask > 0; mask--){
        if(__builtin_popcount(mask) > K) continue;
        array<int, 3> t = {INF, 0, 0};
        for(int i = 0; i < N; i++) if(BIT(mask, i)){
            if(f[mask][i] < t[0]){
                t[0] = f[mask][i];
                t[1] = mask;
                t[2] = i;
            }
        }
        if (t[0] == INF) continue;
        int cur = 0;
        for(int i = 0; i < M; i++){
            int x = queries[i].first, y = queries[i].second;
            if(BIT(mask, x) && BIT(mask, y)){
                cur |= MASK(i);
            }
        }
        if(minimize(g[cur][0], t[0])){
            g[cur][0] = t[0];
            g[cur][1] = t[1];
            g[cur][2] = t[2];
        }
    }
    for(int mask = MASK(M) - 1; mask >= 0; mask--){
        int cur = mask;
        for(int i = 0; i < M; i++) if(!BIT(cur, i)){
            if(minimize(g[cur][0], g[cur | MASK(i)][0])){
                g[cur][1] = g[cur | MASK(i)][1];
                g[cur][2] = g[cur | MASK(i)][2];
            }
        }
    }
    g[0] = {0, 0, 0};


    dp[0] = 0;
    for(int mask = 1; mask < MASK(M); mask++){
        for(int sub = mask; sub > 0; sub = mask & (sub - 1)){
            if(g[sub][0] >= INF) continue;
            if(minimize(dp[mask], dp[mask ^ sub] + g[sub][0]))
                trace_dp[mask] = sub;
        }
    }

    cout << dp[MASK(M) - 1] << ' ';
    int cur = MASK(M) - 1;
    while(cur > 0){
        int t = trace_dp[cur];
        truyvet(g[t][1], g[t][2]);
        cur ^= t;
    }
    cout << save.size() << '\n';
    for(auto V: save){
        cout << V.size() << ' ';
        for(int t: V) cout << t + 1 << ' ';
        cout << '\n';
    }
}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//    freopen("input.inp", "r", stdin);

    int t; cin >> t;
    while(t--)
        solve();

    return 0;
}

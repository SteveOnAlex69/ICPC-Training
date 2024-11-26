#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define sz(x) (int)x.size()
#define ALL(v) v.begin(),v.end()
#define MASK(k) (1LL << (k))
#define BIT(x, i) (((x) >> (i)) & 1)
#define oo (ll)1e18
#define INF (ll)1e9
#define MOD (ll)(1e9 + 7)

using namespace std;

template<class T1, class T2>
    bool maximize(T1 &a, T2 b){if(a < b){a = b; return true;} return false;}

template<class T1, class T2>
    bool minimize(T1 &a, T2 b){if(a > b){a = b; return true;} return false;}

template<class T1, class T2>
    void add(T1 &a, T2 b){a += b; if(a >= MOD) a -= MOD;}

template<class T1, class T2>
    void sub(T1 &a, T2 b){a -= b; if(a < 0) a += MOD;}

template<class T>
    void cps(T &v){sort(ALL(v)); v.resize(unique(ALL(v)) - v.begin());}

const int MAX = 1e5 + 10;

int N, Q;
vector<int> adj[MAX];

void solve(){
    cin >> N;
    for(int i = 1; i < N; i++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    cin >> Q;
    while(Q--){
        int x, y; cin >> x >> y;
        bool ok = false;

        auto dfs = [&](auto self, int u) -> void{
            if(u == y){
                ok = true;
            }
            for(int v: adj[u]){
                self(self, v);
            }
        };

        dfs(dfs, x);

        cout << (ok ? "Yes\n" : "No\n");
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
//     freopen("boat.inp","r",stdin);
//     freopen("boat.out","w",stdout);

    int t = 1;
//    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}

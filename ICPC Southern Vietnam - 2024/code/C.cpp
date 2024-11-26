#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1LL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
 
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
 
ll LASTBIT(ll mask){return (mask) & (-mask);}
int pop_cnt(ll mask){return __builtin_popcountll(mask);}
int ctz(ll mask){return __builtin_ctzll(mask);}
int logOf(ll mask){return 63 - __builtin_clzll(mask);}
 
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
    void printArr(T& container, char separator = ' ', char finish = '\n'){
        for(auto item: container) cout << item << separator;
        cout << finish;
    }
 
template <class T>
    void remove_dup(vector<T> &a){
        sort(ALL(a));
        a.resize(unique(ALL(a)) - a.begin());
    }
 
const int INF = 1e9 + 69;
 
int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int n; cin >> n;
    vector<int> w(n+1), a(n+1), b(n+1);
    for(int i = 1; i<=n; ++i) cin >> w[i];
    for(int i = 1; i<=n; ++i) cin >> a[i];
    for(int i = 1; i<=n; ++i) cin >> b[i];

    vector<int> pos(n+1);
    for(int i = 1; i<=n; ++i) pos[b[i]] = i;

    vector<int> p(n+1);
    for(int i = 1; i<=n; ++i) p[i] = pos[a[i]];

    int mi = *min_element(1 + ALL(w));
    ll ans = 0;
    vector<bool> visited(n+1);
    for(int i = 1; i<=n; ++i) if (!visited[i]){
        int u = i;
        ll sum = 0, cnt = 0, min_cycle = INF;
        while(!visited[u]){
            sum += w[a[u]];
            cnt++;
            minimize(min_cycle, w[a[u]]);
            visited[u] = true;
            u = p[u];
        }

        ll ans1 = (sum - min_cycle) + min_cycle * (cnt - 1);
        ll ans2 = (mi + min_cycle) * 2 + (sum - min_cycle) + mi * (cnt - 1);
        ans += min(ans1, ans2);
    }
    cout << ans << "\n";
 
    return 0;
}

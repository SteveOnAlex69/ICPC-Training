#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return (ull) rng() % (r - l + 1) + l;}

#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

int pop_cnt(ull mask){return __builtin_popcountll(mask);}
int ctz(ull mask){return __builtin_ctzll(mask);}
int logOf(ull mask){return 63 - __builtin_clzll(mask);}

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

const int N = 1e7 + 69;
const int MOD = 1e9 + 7;

ll f[N];

ll fast_pow(ll a, ll n){
    ll ans = 1;
    while(n > 0){
        if (n & 1) ans = ans * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return ans;
}

ll solve(){
    int n, m; cin >> n >> m;
    ll ans = fast_pow(f[m], n) * fast_pow(f[n], m) % MOD;
    return ans;
}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    f[0] = 1;
    for(int i = 1; i < N; ++i) f[i] = f[i-1] * i % MOD;

    int t; cin >> t;
    while(t--) cout << solve() << "\n";

    return 0;
}

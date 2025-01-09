#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return (ull) rng() % (r - l + 1) + l;}

const ll MOD = 998244353;

ll pw(ll a, ll n){
    ll ans = 1;
    while(n){
        if(n & 1) ans = 1LL * ans * a % MOD;
        a = 1LL * a * a % MOD;
        n >>= 1;
    }
    return ans;
}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//    freopen("input.inp", "r", stdin);

    ll S, Q;
    cin >> S >> Q;

    ll cur = 0;

    multiset<pair<ll, ll>> ms;
    while(Q--){
        char t; cin >> t;
        ll w, s; cin >> s >> w;
        if(t == '+'){
            ms.insert({w, s});
            cur += 1LL * s * pw(w, MOD - 2) % MOD;
            if(cur >= MOD) cur -= MOD;
        }
        else{
            ms.erase(ms.find({w, s}));
            cur -= 1LL * s * pw(w, MOD - 2) % MOD;
            if(cur < 0) cur += MOD;
        }

        if(ms.empty()){
            cout << 0 << '\n';
        }
        else{
            auto it = ms.begin();
            ll ans = cur;
            ans += 1LL * S * pw(it->first, MOD - 2) % MOD;
            if(ans >= MOD) ans -= MOD;
            cout << ans << '\n';
        }
    }

    return 0;
}


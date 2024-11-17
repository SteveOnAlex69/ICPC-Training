#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){
    return (ull) rng() % (r - l + 1) + l;
}

ll gcd(ll a, ll b) {return __gcd(a, b);}
ll min(ll a,ll b){return (a > b)? b: a;}
ll max(ll a, ll b){return (a > b)? a: b;}

const int MAX = 7e5 + 10;
const ll MOD = 998244353;

int N, Q;
int a[MAX], pos[MAX], f[MAX], dp[MAX], cnt[MAX], mark[MAX], pre[MAX];

void query(int k){
    for(int i = 0; i <= N; i++){
        mark[i] = k <= i - f[i];
        dp[i] = cnt[i] = 0;
        pre[i] = 0;
    }

    cnt[0] = 1;
    for(int i = 1; i <= N; i++){
        if(mark[i]){
            dp[i] = dp[i - k] + 1;
        }
        else{
            dp[i] = dp[i - 1];
        }
        dp[i] = max(dp[i - 1], dp[i]);
    }
    cnt[0] = 1;
    vector<ll> pref(N+1); pref[0] = 1;
    int p = 0;
    for(int i = 1; i <= N; i++){
        if (dp[i] == dp[i-1]) cnt[i] = (cnt[i] + cnt[i-1]) % MOD;
        if(mark[i]){
            p = max(p, f[i]);
            while(dp[p] < dp[i] - 1) p++;
            cnt[i] = (1LL * cnt[i] + pref[i - k]) % MOD;
            if (p > 0) cnt[i] = (cnt[i] - pref[p - 1] + MOD) % MOD;
        }
        pref[i] = (pref[i - 1] + cnt[i]) % MOD;
//        cout << dp[i] << ' ' << cnt[i] << '\n';
    }
    cout << dp[N] << ' ' << cnt[N] << '\n';
//    cout << '\n';
}

void solve(){
    cin >> N >> Q;
    vector<int> tmp;
    for(int i = 1; i <= N; i++){
        cin >> a[i];
        tmp.push_back(a[i]);
    }
    sort(tmp.begin(), tmp.end());
    tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());

    for(int i = 1; i <= N; i++){
        a[i] = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin();
        pos[a[i]] = 0;
    }
    for(int i = 1; i <= N; i++){
        f[i] = f[i - 1];
        f[i] = max(f[i], pos[a[i]]);
        pos[a[i]] = i;
    }

    while(Q--){
        int k; cin >> k;
        query(k);
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) solve();

    return 0;
}

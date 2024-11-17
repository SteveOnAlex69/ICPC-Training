#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll gcd(ll a, ll b) {return __gcd(a, b);}
ll min(ll a,ll b){return (a > b)? b: a;}
ll max(ll a, ll b){return (a > b)? a: b;}

ll solve(){
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i<n; ++i) cin >> a[i];

    map<int,int> mp;
    for(int i: a) mp[i]++;

    ll ans = 0;
    ll cnt = 0;
    for(auto i: mp){
        if (i.second >= 3){
            ll cur = i.second;
            ans += cur * (cur - 1) * (cur - 2) / 6;
        }
        if (i.second >= 2){
            ll cur = i.second;
            ans += cur * (cur - 1) / 2 * cnt;
        }
        cnt += i.second;
    }

    return ans;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) cout << solve() << "\n";

    return 0;
}

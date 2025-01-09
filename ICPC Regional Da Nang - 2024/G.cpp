#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return (ull) rng() % (r - l + 1) + l;}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int tt; cin >> tt;
    while(tt--){
        int n; cin >> n;
        vector<int> a(n + 3, 0);
        for(int i = 1; i <= n; i++){
            cin >> a[i];
        }
        sort(a.begin() + 1, a.begin() + n + 1);
        int ans = min(a[n - 1] - a[1], a[n] - a[2]);
        cout << ans << '\n';
    }

    return 0;
}


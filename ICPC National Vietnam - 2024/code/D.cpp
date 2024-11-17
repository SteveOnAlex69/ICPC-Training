#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll gcd(ll a, ll b) {return __gcd(a, b);}
ll min(ll a,ll b){return (a > b)? b: a;}
ll max(ll a, ll b){return (a > b)? a: b;}

string solve(){
    int a, b, c, t; cin >> a >> b >> c >> t;
    t %= (a + b + c);
    if (t < a) return "Guiding Beat";
    else if (t < a + b) return "Warning Beat";
    return "Resting Phase";
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) cout << solve() << "\n";

    return 0;
}

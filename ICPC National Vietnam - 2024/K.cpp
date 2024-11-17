#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll gcd(ll a, ll b) {return __gcd(a, b);}
ll min(ll a,ll b){return (a > b)? b: a;}
ll max(ll a, ll b){return (a > b)? a: b;}

bool solve(){
    int n, a, b; cin >> n >> a >> b;
    string s; cin >> s;

        s = "#" + s;
    if (a < b){
        if (a <= n / 2) return true;
        int r = a, l = n - a + 1;
        for(int i = l + 1; i <= r; ++i) if (s[i] != s[i-1]) return false;
        return true;
    }
    else{
        for(int i = 1; i <= n - a + 1; ++i){
            if (s[i] == '0'){
                for(int j = 0; j < a; ++j) s[i + j] ^= 1;
            }
        }
        for(int i = 1; i <= n; ++i) if (s[i] == '0') return false;
        return true;
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) if (solve()) cout << "YES\n";
        else cout  << "NO\n";

    return 0;
}

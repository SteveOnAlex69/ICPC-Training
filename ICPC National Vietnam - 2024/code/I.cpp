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

string try_minimize(string s){
    int n = s.size();
    for(int j = n - 2; j >= 0; --j){
        for(int i = j; i + 1 < n; ++i){
            if (s[i] == '1'){
                if (s[i] == s[i+1]){
                    s[i] = s[i+1] = '0';
                }
                else if (i + 2 < n && s[i + 1] == '0' && s[i+2] == '0'){
                    s[i] = '0';
                    s[i+2] = '1';
                }
                else break;
            }
        }
    }
    return s;
}

bool solve(){
    int n; cin >> n;
    string a, b; cin >> a >> b;

    return try_minimize(a) == try_minimize(b);
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) if (solve()) cout << "YES\n";
    else cout << "NO\n";

    return 0;
}

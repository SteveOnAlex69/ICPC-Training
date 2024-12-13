#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return (ull) rng() % (r - l + 1) + l;}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//    freopen("input.inp", "r", stdin);

    int tt; cin >> tt;
    while(tt--){
        int n; cin >> n;
        string s; cin >> s;

        if(s == "fizz"){
            if(n <= 2) cout << "1 3\n";
            else cout << "1 " << n - 1 << '\n';
        }
        else if(s == "buzz"){
            int t = -1;
            for(int i = 1; i <= n; i++){
                if(n % i != 0){
                    t = i;
                    break;
                }
            }
            if(t == -1){
                cout << "-1 -1\n";
            }
            else{
                cout << t << ' ' << n << '\n';
            }
        }
        else if(s == "fizzbuzz"){
            if(n == 1){
                cout << "-1 -1\n";
            }
            else{
                cout << 1 << ' ' << n << '\n';
            }
        }
        else{
            if(n + 2 <= (int)1e9){
                cout << n + 1 << ' ' << n + 2 << '\n';
            }
            else{
                cout << n - 2 << ' ' << n - 1 << '\n';
            }
        }
    }

    return 0;
}

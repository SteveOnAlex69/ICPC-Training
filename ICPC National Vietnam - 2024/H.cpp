#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll gcd(ll a, ll b) {return __gcd(a, b);}
ll min(ll a,ll b){return (a > b)? b: a;}
ll max(ll a, ll b){return (a > b)? a: b;}

void solve(){
    int n; cin >> n;
    int x; cin >> x;

    vector<int> a(n);
    int smaller = 0, bigger = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] == -1) continue;
        if(a[i] < x) smaller++;
        if(a[i] > x) bigger++;
    }

    if(smaller * 2 > n || bigger * 2 > n){
        cout << "NO\n";
    }
    else{
        cout << "YES\n";
        for(int i = 0; i < n; i++){
            if(a[i] == -1){
                cout << x << ' ';
                continue;
            }
            if(a[i] < x || a[i] > x){
                cout << a[i] << ' ';
            }
            else{
                cout << x << ' ';
            }
        }
        cout << '\n';
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) solve();

    return 0;
}

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define sz(x) (int)x.size()

#define ALL(v) (v).begin(), (v).end()
#define MASK(i) (1LL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(1);
ll rngesus(ll l, ll r){return ((ull) rng()) % (r - l + 1) + l;}

ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
ll gcd(ll a, ll b){return __gcd(a, b);}

ll LASTBIT(ll mask){return mask & (-mask);}
ll pop_cnt(ll mask){return __builtin_popcountll(mask);}
ll ctz(ll mask){return __builtin_ctzll(mask);}
ll clz(ll mask){return __builtin_clzll(mask);}
ll logOf(ll mask){return 63 - clz(mask);}

template <class T1, class T2>
    bool minimize(T1 &a, T2 b){
        if (a > b){a = b; return true;}
        return false;
    }
template <class T1, class T2>
    bool maximize(T1 &a, T2 b){
        if (a < b){a = b; return true;}
        return false;
    }
template <class T>
    void printArr(T a, string separator = " ", string finish = "\n", ostream& out = cout){
        for(auto i: a) out << i << separator;
        out << finish;
    }
template <class T>
    void remove_dup(vector<T> &a){
        sort(ALL(a));
        a.resize(unique(ALL(a)) - a.begin());
    }

const int MAX = 5e4 + 10;

ll solve(){
    int n; cin >> n;
    vector<int> a(n + 3, 0);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<int> L(n + 3, 0), R(n + 3, 0);
    for(int i = 1; i <= n; i++){
        L[i] = min(L[i - 1] + 1, a[i]);
    }
    for(int i = n; i >= 1; i--){
        R[i] = min(R[i + 1] + 1, a[i]);
    }
    int ans = 0;
    for(int i = 1; i <= n; i++){
        maximize(ans, min(L[i], R[i]));
    }
    return ans;
}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);


    int t = 1;
    // cin >> t;
    while(t--) cout << solve() << "\n";

    return 0;
}

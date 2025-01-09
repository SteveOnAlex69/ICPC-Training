#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return (ull) rng() % (r - l + 1) + l;}

#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

ll gcd(ll a, ll b){return __gcd(a, b);}
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
int pop_cnt(ull mask){return __builtin_popcountll(mask);}
int ctz(ull mask){return __builtin_ctzll(mask);}
int logOf(ull mask){return 63 - __builtin_clzll(mask);}

template <class T1, class T2>
    bool maximize(T1 &a, T2 b){
        if (a < b){a = b; return true;}
        return false;
    }
template <class T1, class T2>
    bool minimize(T1 &a, T2 b){
        if (a > b){a = b; return true;}
        return false;
    }
template <class T>
    void printArr(T &a){
        for (auto i: a) cout << i << " ";
        cout << "\n";
    }
template <class T>
    void remove_dup(vector<T> &a){
        sort(ALL(a));
        a.resize(unique(ALL(a)) - a.begin());
    }

int get_between(vector<int> &a, int l, int r){
    return upper_bound(ALL(a), r) - lower_bound(ALL(a), l);
}

void solve(){
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i<n; ++i) cin >> a[i];

    sort(ALL(a));
    vector<int> b = a; remove_dup(b);
    int ans = n * 2;
    for(int i: b){
        int cnt1 = get_between(a, i, i);
        int cnt2 = get_between(a, i+1, 1e9 + 69) - get_between(a, i*2, i*2);

        if (cnt1 > cnt2){
            ll cost = 0;
            for(int j: a){
                cost += (j / i) + 2 * (j % i != 0);
                if (cost >= ans) break;
            }
            minimize(ans, cost);
        }
    }
    cout << ans << "\n";
}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//    freopen("input.inp", "r", stdin);

    int t; cin >> t;
    while(t--) solve();

    return 0;
}


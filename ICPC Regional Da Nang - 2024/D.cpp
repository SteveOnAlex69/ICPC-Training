#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return (ull) rng() % (r - l + 1) + l;}

#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

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

void solve(){
    int n; ll k; cin >> n >> k;
    vector<int> ans(n+1);
    int l = 1, r = n;
    int cur = n;
    while(r - l > 60){
        ans[r--]= cur--;
    }
    while(l < r){
        ll cnt = MASK(r - l - 1);
        if (k > cnt) {
            k -= cnt;
            ans[l++]= cur--;
        }
        else{
            ans[r--] = cur--;
        }
    }
    ans[l] = cur--;
    for(int i= 1; i <= n; ++i) cout << ans[i] << " ";
    cout << "\n";
}


int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//    freopen("input.inp", "r", stdin);

    int t; cin >> t;
    while(t--) solve();

    return 0;
}


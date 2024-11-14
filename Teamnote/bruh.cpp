#include <bits/stdc++.h>
#define MP make_pair
#define fi first
#define se second
#define vi vector<int>
#define sz(a) (int)(a.size())
#define all(a) a.begin(), a.end()
 
using namespace std;
 
typedef long long ll;
typedef unsigned int ul;
typedef unsigned long long ull;
 
#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
 
ll gcd(ll a, ll b){return __gcd(a, b);}
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
 
ll LASTBIT(ll mask){return (mask) & (-mask);}
int pop_cnt(ll mask){return __builtin_popcountll(mask);}
int ctz(ull mask){return __builtin_ctzll(mask);}
int logOf(ull mask){return 63 - __builtin_clzll(mask);}

const int maxn = 1e5;
const ll  inf  = 1e18;
const ll  mod  = 1e9 + 7;

template<class T1,class T2>
bool maximize(T1 &a,T2 b){
    if(a < b){
        a = b;
        return 1;
    }
    return 0;
}

template<class T1,class T2>
bool minimize(T1 &a,T2 b){
    if(a > b){
        a = b;
        return 1;
    }
    return 0;
}

ll n, m;
ll a[maxn + 5];

bool check_sub1(){
    return (m <= n);
}

namespace sub1 {
    void solve(){
        multiset<ll> s;
        for(int i = 1; i <= n; ++i) s.insert(a[i]);
        for(int i = 0; i < m; ++i){
            auto it = s.begin();
            ll val = *it;
            s.erase(it);
            val = val * val;
            s.insert(val);
        }
        for(auto x : s) cout<<x % mod<<' ';
        return;
    }
}

ll fast_pow(ll a,ll b,ll modu){
    ll res = 1LL;
    for(; b > 0; b >>= 1LL, a = a * a % modu) if(b & 1LL)
        res = res * a % modu;
    return res;
}

namespace sub4 {
    void solve(){
        multiset<ll> s;
        for(int i = 1; i <= n; ++i) s.insert(a[i]);
        while(m){
            --m;
            ll val = *s.begin();
            s.erase(s.begin());
            bool ok = (val > *s.rbegin() / val);
            if(ok) break;
            s.insert(val * val);
        }
        if(!m){
            assert(0);
            for(ll val : s) cout<<val % mod<<' ';
            return;
        }
        ll div = m / n;
        ll remain = m % n;
        ll pw[2];
        pw[0] = fast_pow(2LL, div, mod - 1);
        pw[1] = fast_pow(2LL, div + 1LL, mod - 1);
        for(ll val : s){
            int check = (remain != 0);
            if(check) --remain;
            ll time = pw[check];
            cout<<fast_pow(val, time, mod)<<' ';
        }
        return;
    }
}

void input(){
    cin>>n>>m;
    for(int i = 1; i <= n; ++i) cin>>a[i];
    return;
}

int main(){
    // ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    input();
    // if(check_sub1()) return sub1::solve(), 0;
    sub4::solve();

    return 0;
}

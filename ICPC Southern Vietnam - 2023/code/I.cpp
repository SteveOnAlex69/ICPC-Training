#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define ll long long
#define el '\n'
#define fu(i,a,b) for(int i = (a), _b = (b); i <= _b; ++i)
#define fd(i,a,b) for(int i = (a), _b = (b); i >= _b; --i)
#define fa(x, a) for(auto x : a)
#define re(i, n) fu(i,0,n - 1)
#define vi vector<int>
#define vvi vector<vi>
#define vll vector<ll>
#define vvll vector<vll>
#define pb push_back
#define pf push_front
#define pof pop_front
#define pob pop_back
#define sz(a) (int)(a.size())
#define all(a) a.begin(), a.end()
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define vpll vector<pll>
#define vvpll vector<vpll>
#define MP make_pair
#define fi first
#define se second
#define MASK(i) (1LL << (i))
#define db double
#define ld long double

using namespace std;

const int maxn = 2e5;
const int lim  = 1e6;
const ll  inf  = 1e16;
const ll  mod  = 1e9 + 7; /// 1007050321
const ll  base = 33137;

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

template<class T1,class T2>
void Add(T1 &a,T2 b){
    a += b;
    if(a >= mod) a -= mod;
    if(a < 0) a += mod;
    return;
}

template<class T1>
void compress(vector<T1> &a){
    sort(all(a));
    a.resize(unique(all(a)) - a.begin());
    return;
}

bool takeBit(ll th,ll n){return ((n >> th) & 1LL);}

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch(). count());
#define rand rd

ll ran(ll lo,ll hi){
    return (lo + rand() % (hi - lo + 1));
}

//int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
//int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

int n;
ll a[5005], dp[5005];

void solve(){
    // dp[0] = 1LL;
    ll res = 0LL;
    sort(a + 1,a + 1 + n);
    ll sum = min(a[1] + a[2], 5001LL);
    dp[sum] = 1LL;
    fu(i,3,n){
        fu(j,a[i] + 1,5001) Add(res, dp[j]);
        fd(j,5001,0) if(dp[j]){
            ll nval = min(j + a[i], 5001LL);
            Add(dp[nval], dp[j]);
        }
        fu(j,1,i - 1){
            sum = min(a[j] + a[i], 5001LL);
            Add(dp[sum], 1LL);
        } 
        // cout<<i<<' '<<res<<el;
    }
    cout<<res;
    return;
}

void input(){
    cin>>n;
    fu(i,1,n) cin>>a[i];
    return;
}

int main(){
    fast
    input();
    solve();
    return 0;
}

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

const int maxn = 1e5;
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
int a[maxn + 5], pre[maxn + 5];
int _lef[maxn + 5], _rig[maxn + 5];

struct SegTree
{
    vpii seg;

    SegTree() = default;
    SegTree(int n) : seg(4 * n + 5) {}

    void init(int id,int l,int r){
        if(l > r) return;
        if(l == r){
            seg[id] = MP(pre[l], pre[l]);
            return;
        }
        int mid = (l + r) >> 1;
        init(id<<1,l,mid);
        init(id<<1|1,mid + 1,r);
        seg[id].fi = max(seg[id<<1].fi, seg[id<<1|1].fi);
        seg[id].se = min(seg[id<<1].se, seg[id<<1|1].se);
        return;
    }

    pii query(int id,int l,int r,int lo,int hi){
        if(l > r) return MP(-mod, mod);
        if(hi < l || r < lo) return MP(-mod, mod);
        if(lo <= l && r <= hi) return seg[id];
        int mid = (l + r) >> 1;
        pii tmp1 = query(id<<1,l,mid,lo,hi);
        pii tmp2 = query(id<<1|1,mid + 1,r,lo,hi);
        pii res = MP(max(tmp1.fi, tmp2.fi), min(tmp1.se, tmp2.se));
        return res;
    }
};

void preprocess(){
    fu(i,1,n) pre[i] = pre[i - 1] + a[i];
    stack<int> st;
    st.push(0);
    fu(i,1,n){
        while(sz(st) > 1 && a[st.top()] <= a[i]) st.pop();
        _lef[i] = st.top();
        st.push(i);
    }
    while(!st.empty()) st.pop();
    st.push(n + 1);
    fd(i,n,1){
        while(sz(st) > 1 && a[st.top()] <= a[i]) st.pop();
        _rig[i] = st.top();
        st.push(i);
    }
    return;
}

void solve(){
    preprocess();
    SegTree IT(n);
    IT.init(1,1,n);
    ll res = 0;
    fu(i,1,n){  
        int l = _lef[i], r = _rig[i] - 1;
        // cout<<i<<' '<<l<<' '<<r<<' ';
        pii tmp1 = IT.query(1,1,n,max(1, l),i - 1);
        if(!l) minimize(tmp1.se, 0);
        pii tmp2 = IT.query(1,1,n,i,r);
        ll sum = tmp2.fi - tmp1.se - a[i];
        // cout<<sum + a[i]<<' '<<tmp1.se<<' '<<tmp2.fi<<el;
        maximize(res, sum);
        // cout<<res<<el;
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
//    freopen("planting.in", "r", stdin);
//    freopen("planting.out", "w", stdout);
    input();
    solve();
    return 0;
}

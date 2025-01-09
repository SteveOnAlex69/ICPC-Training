#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
 
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
ll gcd(ll a, ll b){return __gcd(a, b);}
ll lcm(ll a, ll b){return a / gcd(a, b) * b;}
 
ll LASTBIT(ll mask){return (mask) & (-mask);}
int pop_cnt(ull mask){return __builtin_popcountll(mask);}
int ctz(ull mask){return __builtin_ctzll(mask);}
int logOf(ull mask){return 63 - __builtin_clzll(mask);}
 
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return l + (ull) rng() % (r - l + 1);}
double rngesus_d(double l, double r){
    double cur = rngesus(0, MASK(60) - 1);
    cur /= MASK(60) - 1;
    return l + cur * (r - l);
}
 
template <class T1, class T2>
    bool maximize(T1 &a, T2 b){
        if (a < b) {a = b; return true;}
        return false;
    }
 
template <class T1, class T2>
    bool minimize(T1 &a, T2 b){
        if (a > b) {a = b; return true;}
        return false;
    }
 
template <class T>
    void printArr(T container, string separator = " ", string finish = "\n", ostream &out = cout){
        for(auto item: container) out << item << separator;
        out << finish;
    }
 
template <class T>
    void remove_dup(vector<T> &a){
        sort(ALL(a));
        a.resize(unique(ALL(a)) - a.begin());
    }


const ll INF = 1e18 + 69;

struct SegmentTree{
    int n;
    vector<ll> a;

    SegmentTree(int _n){
        n = _n;
        a.resize(n * 2 + 2, INF);
    }

    void update(int i, int v){
        i += n; a[i] = v;
        while(i > 1){
            i >>= 1;
            a[i] = min(a[i * 2], a[i * 2 + 1]);
        }
    }

    ll get(int l, int r){
        l += n; r += n + 1;
        ll ans = INF;
        while(l < r){
            if (l & 1) minimize(ans, a[l++]);
            if (r & 1) minimize(ans, a[--r]);
            l >>= 1; r >>= 1;
        }
        return ans;
    }
};

ll calc_sum(ll l, ll r){
    return (l + r) * (r - l + 1) / 2;
}

ll calc_single_cost(int n, int x, int i, int r, vector<int> &pref, vector<ll> &pref_idx){
    int l = r - n + 1;

    int L = 0, R = x;
    while(L < R){
        int M = (L + R) >> 1;
        int cur = pref[i + M - 1] - pref[l - 1];
        if (M < cur) L = M + 1;
        else R = M;
    }

    ll ans = calc_sum(i, i - 1 + L) - (pref_idx[i + L - 1] - pref_idx[l - 1]);
    ans += (pref_idx[r] - pref_idx[i + L - 1]) - calc_sum(i + L, i + x - 1);
    return ans;
}

void dnc(int n, int x, int l, int r, int optL, int optR, vector<int> &pref, vector<ll> &pref_idx, vector<ll> &cost){
    if (l > r) return;
    int mid = (l + r) >> 1;
    int L = mid + x - 1, R = mid + n - 1;
    maximize(L, optL); minimize(R, optR);
    int opt = -1;
    for(int i = L; i <= R; ++i){
        if (minimize(cost[mid], calc_single_cost(n, x, mid + n, i + n, pref, pref_idx))){
            opt = i;
        }
    }
    dnc(n, x, l, mid - 1, optL, opt, pref, pref_idx, cost);
    dnc(n, x, mid + 1, r, opt, optR, pref, pref_idx, cost);

}

vector<ll> calc_cost(int n, int x, vector<int> a){
    vector<int> pref(n * 3 + 1);
    vector<ll> pref_idx(n * 3 + 1);
    for(int i: a){
        pref[i]++;
        pref[i + n]++;
        pref[i + n * 2]++;

        pref_idx[i] += i;
        pref_idx[i+n] += i+n;
        pref_idx[i + n * 2] += i + n * 2;
    }
    for(int i = 1; i <= n * 3; ++i) pref[i] += pref[i-1];
    for(int i = 1; i <= n * 3; ++i) pref_idx[i] += pref_idx[i-1];

    vector<ll> cost(n+1, INF);
    dnc(n, x, 1, n, x, 2*n-1, pref, pref_idx, cost);
    // printArr(cost);
    return cost;
}


ll solve(){
    int n, x, y; cin >> n >> x >> y;
    vector<int> a(x), b(y);
    for(int i = 0; i<x; ++i) cin >> a[i];
    for(int i = 0; i<y; ++i) cin >> b[i];

    vector<ll> cost1 = calc_cost(n, x, a);
    vector<ll> cost2 = calc_cost(n, y, b);

    for(int i = 1; i <= n; ++i) cost2.push_back(cost2[i]);
    SegmentTree st(n * 2);
    for(int i = 1; i <= n * 2; ++i) st.update(i, cost2[i]);
    ll ans = INF;
    for(int i = 1; i <= n; ++i){
        ll cur = cost1[i] + st.get(i + x, i + (n - y));
        minimize(ans, cur);
    }

    return ans;
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

    freopen("CYCLE.INP", "r", stdin);
    freopen("CYCLE.OUT", "w", stdout);

    clock_t start = clock();

    int t; cin >> t;
    while(t--) cout << solve() << "\n";

    cerr << "Time elapsed: " << clock() - start << " ms\n";
    return 0;
}
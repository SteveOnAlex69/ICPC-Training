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

const int INF = 1e9 + 69;

struct FenwickTree{
    int n;
    vector<int> a;

    FenwickTree(int _n){
        n = _n;
        a.resize(n+1);
    }

    void update(int i, int v){
        while(i <= n){
            a[i] += v;
            i += LASTBIT(i);
        }
    }

    int get(int i){
        int ans = 0;
        while(i > 0){
            ans += a[i];
            i -= LASTBIT(i);
        }
        return ans;
    }
};

struct SegmentTree{
    int n, h;
    vector<int> t, d;
 
    SegmentTree(int _n){
        n = _n;
        h = logOf(n);
        t.resize(n * 2 + 2), d.resize(n * 2 + 2);
        for(int i = 1; i <= n * 2 + 1; ++i) t[i] = d[i] = 0;
    }
 
    void apply(int p, int value) {
        t[p] += value;
        if (p < n) d[p] += value;
    }
 
    void build(int p) {
        while (p > 1) p >>= 1, t[p] = min(t[p<<1], t[p<<1|1]) + d[p];
    }
 
    void push(int p) {
      for (int s = h; s > 0; --s) {
        int i = p >> s;
        if (d[i] != 0) {
          apply(i<<1, d[i]);
          apply(i<<1|1, d[i]);
          d[i] = 0;
        }
      }
    }
 
    void update(int l, int r, int value) {
      l += n, r += n+1;
      int l0 = l, r0 = r;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) apply(l++, value);
        if (r&1) apply(--r, value);
      }
      build(l0);
      build(r0 - 1);
    }
 
    int get() {
        int l = 1, r = n;
      l += n, r += n+1;
      push(l);
      push(r - 1);
      int res = INF;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) res = min(res, t[l++]);
        if (r&1) res = min(t[--r], res);
      }
      return res;
    }
};

const int N = 2e6 + 69;
vector<int> skibidi[N], sigma[N];

ll solve(){
    int n, m; cin >> n >> m;
    vector<int> a(n+1), b(m+1);
    for(int i= 1; i<=n; ++i) cin >> a[i];
    for(int i= 1; i<=m; ++i) cin >> b[i];

    ll ans = 0;
    vector<int> c = a;
    for(int i: b) c.push_back(i);
    remove_dup(c);

    for(int i = 1; i<=n; ++i) a[i] = lower_bound(ALL(c), a[i]) - c.begin();
    for(int i = 1; i<=m; ++i) b[i] = lower_bound(ALL(c), b[i]) - c.begin();

    int k = c.size() - 1;
    FenwickTree bit(k);
    for(int i = n; i>=1; --i){
        ans += bit.get(a[i] - 1);
        bit.update(a[i], 1);
    }

    for(int i = 0; i <= k; ++i){
        skibidi[i].clear();
        sigma[i].clear();
    }
    for(int i= 1; i<=n; ++i) skibidi[a[i]].push_back(i);
    for(int i=1; i<=m; ++i) sigma[b[i]].push_back(i);

    SegmentTree st(n + 1);
    for(int i = 2; i <= n + 1; ++i) st.update(i, n + 1, 1);
    for(int i = 1; i <= k; ++i){
        for(int j: skibidi[i]){
            st.update(j + 1, n + 1, -1);
        }
        for(int j: sigma[i]){
            ans += st.get();
        }
        for(int j: skibidi[i]){
            st.update(1, j, 1);
        }

    }

    return ans;

}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);


    int t; cin >> t;
    while(t--) cout << solve() << "\n";

    return 0;
}

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


 
const int MOD = 1e9 + 7;
struct Modular{
    ll x;
    Modular(ll _x = 0){
        x = _x % MOD;
        if (x < 0) x += MOD;
    }
    Modular& operator += (Modular y){
        x += y.x;
        if (x >= MOD) x -= MOD;
        return *this;
    }
    Modular operator + (Modular y) {
        Modular tmp = *this;
        return tmp += y;
    }
 
    Modular& operator -= (Modular y){
        x -= y.x;
        if (x < 0) x += MOD;
        return *this;
    }
    Modular operator - (Modular y) {
        Modular tmp = *this;
        return tmp -= y;
    }
 
    Modular& operator *= (Modular y){
        x *= y.x;
        if (x >= MOD) x %= MOD;
        return *this;
    }
    Modular operator * (Modular y) {
        Modular tmp = *this;
        return tmp *= y;
    }
 
    // use at your own risk
    bool operator == (Modular y){
        return x == y.x;
    }
    bool operator != (Modular y){
        return x != y.x;
    }
};
ostream& operator << (ostream& out, Modular x){
    out << x.x;
    return out;
}

Modular fast_pow(Modular a, int n){
    Modular ans = 1;
    while(n > 0){
        if (n & 1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}
Modular inverse(Modular a){return fast_pow(a, MOD - 2);}

const int N = 1e6 + 69;
vector<Modular> fact(N), ifact(N);

void prepare(){
    fact[0] = 1;
    for(int i = 1; i<N; ++i) fact[i] = fact[i-1] * i;
    ifact[N - 1] = inverse(fact[N-1]);
    for(int i = N-1; i>=1; --i) ifact[i-1] = ifact[i] * i;
}

Modular C(int n, int k){
    if (k < 0 || k > n) return 0;
    return fact[n] * ifact[k] * ifact[n-k];
}

int calc(int n, int k, vector<int> &a, vector<int> &p){
    int m = 0;
    for(int i = 1; i < n; ++i){
        if (a[i] != n && a[i+1] != n){
            int x = p[a[i]+1], y = p[a[i+1]+1];
            if (x < y) m++;
        }
        else if (a[i] == n){
            m++;
        }
    }

    return m;
}

void solve(){
    int n, k, q; cin >> n >> k >> q;
    vector<int> a(n+1);
    for(int i = 1; i<=n; ++i) cin >> a[i];

    for(int i = 1; i <= n; ++i) a[i] = n - a[i] + 1;

    vector<int> p(n+1);
    for(int i = 1; i <= n; ++i) p[a[i]] = i;

    int m = calc(n, k, a, p);
    cout << C(m + k, n) << "\n";
    while(q--){
        int i, j; cin >> i >> j;

        vector<int> necessary_pos;
        necessary_pos.push_back(i - 1);
        necessary_pos.push_back(i);
        necessary_pos.push_back(j - 1);
        necessary_pos.push_back(j);

        int _i = p[a[i] - 1], _j = p[a[j] - 1];
        necessary_pos.push_back(_i); necessary_pos.push_back(_i - 1);
        necessary_pos.push_back(_j); necessary_pos.push_back(_j - 1);

        remove_dup(necessary_pos);

        for(int i: necessary_pos) if (0 < i && i < n){
            if (a[i] != n && a[i+1] != n){
                int x = p[a[i]+1], y = p[a[i+1]+1];
                if (x < y) m--;
            }
            else if (a[i] == n){
                m--;
            }
        }

        swap(a[i], a[j]);
        swap(p[a[i]], p[a[j]]);

        for(int i: necessary_pos) if (0 < i && i < n){
            if (a[i] != n && a[i+1] != n){
                int x = p[a[i]+1], y = p[a[i+1]+1];
                if (x < y) m++;
            }
            else if (a[i] == n){
                m++;
            }
        }

        cout << C(m + k, n) << "\n";
    }
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

    freopen("ENCODE.INP", "r", stdin);
    freopen("ENCODE.OUT", "w", stdout);

    clock_t start = clock();

    prepare();
    solve();

    cerr << "Time elapsed: " << clock() - start << " ms\n";
    return 0;
}
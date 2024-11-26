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
 
const int MOD = 1e9 + 7;
struct Modular{
    ll x;
    Modular(ll _x = 0){x = _x;}
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

struct Fib{
    Modular po1, po2, sum2, sum3;
    Fib(Modular po1, Modular po2, Modular sum2, Modular sum3): 
    po1(po1), po2(po2), sum2(sum2), sum3(sum3){}

    bool operator < (Fib x) const{
        array<ll, 4> a1 = {{po1.x, po2.x, sum2.x, sum3.x}};
        array<ll, 4> a2 = {{x.po1.x, x.po2.x, x.sum2.x, x.sum3.x}};
        return a1 < a2;
    }

    void scale(Modular f){
        po1 *= f, po2 *= f, sum2 *= f, sum3 *= f;
    }
};

Fib combine(Fib a, Fib b){
    Fib c(a.po1 * b.po1, a.po2 * b.po1 + a.po1 * b.po2, 0, 0);
    c.sum2 += a.sum2 * b.po1 + b.sum2 * a.po1;
    c.sum3 += a.sum3 * b.po1 + b.sum3 * a.po1 + a.sum2 * b.po2 + b.sum2 * a.po2;
    return c;
}

Fib fast_pow(Fib a, int n){
    if (n == 0) return Fib(1, 0, 0, 0);
    if (n == 1) return a;
    Fib t = fast_pow(a, n/2);
    if (n % 2 == 0) return combine(t, t);
    return combine(t, combine(t, a));
}

int o_cnt = 0;
namespace Fibonacci{
    
    const ll MOD1 = 1e9 + 7;        // First modulus
    const ll MOD2 = 1e9 + 6;        // Second modulus
    const ll MOD = MOD1 * MOD2;     // Combined modulus

    // Custom modular multiplication function
    ll modMul(ll a, ll b) {
        ll res = 0;
        a %= MOD;
        while (b) {
            o_cnt++;
            res = (res + a * (b & 7)) % MOD;
            a = (8 * a) % MOD;
            b >>= 3;
        }
        return res;
    }

    // Struct to return both F(n) and F(n+1)
    struct FibPair {
        ll fn;    // F(n)
        ll fn1;   // F(n+1)
    };

    // Recursive divide and conquer Fibonacci function
    FibPair fib(ll n) {
        if (n == 0)
            return {0, 1};

        // Recursively calculate Fibonacci for n/2
        FibPair half = fib(n / 2);

        // Use the divide and conquer formula
        ll fn = half.fn;
        ll fn1 = half.fn1;

        // F(2n) = F(n) * (2F(n+1) - F(n))
        ll c = modMul(fn, modMul(2 * fn1 - fn + MOD, 1));

        // F(2n+1) = F(n+1)^2 + F(n)^2
        ll d = modMul(fn1, fn1) + modMul(fn, fn);

        if (n % 2 == 0) {
            return {c % MOD, d % MOD};
        } else {
            return {d % MOD, (c + d) % MOD};
        }
    }

    // Compute nth Fibonacci number given a, b as F(0) and F(1)
    pair<ll, ll> fibonacci(ll n) {
        FibPair result = fib(n - 1);

        // F(n) = F(n-1) * b + F(n-2) * a
        return make_pair(result.fn, result.fn1);
    }

}

Modular solve(){
    int n; cin >> n;
    if (n == 0) return 0;
    if (n == 1) return 1;
    pair<ll, ll> y = Fibonacci::fibonacci(n);
    Fib left = fast_pow(Fib(2, 1, 0, 0), y.first % MOD);
    Modular f1 = fast_pow(2, y.first / MOD);
    left.scale(f1);

    Fib right = fast_pow(Fib(2, 1, 1, 1), y.second % MOD);
    Modular f2 = fast_pow(2, y.second / MOD);
    right.scale(f2);

    return combine(left, right).sum3;
}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    clock_t start = clock();
    int t; cin >> t;
    while(t--) cout << solve() << "\n";

    cerr << "time elapsed: " << clock() - start << "ms\n";
    cerr << "operation: " << o_cnt << "\n";
    return 0;
}

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;


mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){
    return (ull) rng() % (r - l + 1) + l;
}

ll gcd(ll a, ll b) {return __gcd(a, b);}
ll min(ll a,ll b){return (a > b)? b: a;}
ll max(ll a, ll b){return (a > b)? a: b;}

const int MOD = 998244353;
struct Modular{
    ll x;
    Modular(ll _x = 0){
        x = _x % MOD;
        if (x < 0) x += MOD;
    }

    Modular& operator += (Modular y){
        x += y.x;
        if (x > MOD) x -= MOD;
        return *this;
    }
    Modular& operator -= (Modular y){
        x -= y.x;
        if (x < 0) x += MOD;
        return *this;
    }
    Modular& operator *= (Modular y){
        x *= y.x;
        x %= MOD;
        return *this;
    }

    Modular operator + (Modular y) {
        Modular tmp = *this;
        return tmp += y;
    }
    Modular operator - (Modular y) {
        Modular tmp = *this;
        return tmp -= y;
    }
    Modular operator * (Modular y) {
        Modular tmp = *this;
        return tmp *= y;
    }
};

ostream& operator << (ostream& out, Modular x){
    out << x.x;
    return out;
}

Modular fast_pow(Modular a, ll n){
    Modular ans = 1;
    while(n){
        if (n & 1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}
Modular inverse(Modular a){return fast_pow(a, MOD - 2);}

struct Matrix{
    int n, m;
    vector<vector<Modular>> a;

    Matrix(int _n, int _m){
        n = _n, m = _m;
        a = vector<vector<Modular>>(n, vector<Modular>(m));
    }

    Matrix operator * (Matrix b) {
        if (m != b.n) assert(false);
        Matrix res(n, b.m);
        for(int i = 0; i < n; ++i)
        for(int k = 0; k < m; ++k)
        for(int j = 0; j < b.m; ++j)
            res.a[i][j] += a[i][k] * b.a[k][j];
        return res;
    }
};

Matrix fast_pow(Matrix a, ll n){
    if (n == 1) return a;
    Matrix t = fast_pow(a, n / 2);
    if (n % 2 == 0) return t * t;
    return t * t * a;
}

Modular inv3 = inverse(3);
Matrix T(6, 6);
vector<vector<Matrix>> tower;

void prepare(){

    T.a[5][5] = 1;
    T.a[0][1] = T.a[1][2] = T.a[2][3] = T.a[3][4] = 1;
    T.a[5][0] = 1;
    T.a[2][0] = T.a[3][0] = T.a[4][0] = inv3;
    tower.push_back({T});
    for(int i = 0; i < 30; ++i){
        if (i > 0){
            tower.push_back({tower[i-1][0] * tower[i-1].back()});
        }
        for(int j = 1; j < 3; ++j){
            tower[i].push_back(tower[i][0] * tower[i].back());
        }
    }
}

Modular solve(){
    Modular ans = 0;
    int n; cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];

    for(ll i: a){
        Matrix A(1, 6);
        A.a[0][5] = 1;

        for(int j = 0; j < 30; ++j) {
            if (i % 4) A = A * tower[j][i % 4 - 1];
            i /= 4;
        }
        ans += A.a[0][0];
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    prepare();

    int t; cin >> t;
    while(t--) cout << solve() << "\n";

    return 0;
}

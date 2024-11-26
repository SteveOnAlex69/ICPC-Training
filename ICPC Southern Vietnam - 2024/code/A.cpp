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

const int N = 110;

int a[N][N][N];
struct BIT3D{
    vector<vector<vector<ll>>> tree;
    int n;

    BIT3D(int _n = 0){
        n = _n;
        tree.assign(n + 1, vector<vector<ll>>(n + 1, vector<ll>(n + 1, 0)));
    }

    void upd(int x, int y, int z, ll c){
        for(int i = x; i <= n; i += i & -i){
            for(int j = y; j <= n; j += j & -j){
                for(int k = z; k <= n; k += k & -k){
                    tree[i][j][k] += c;
                }
            }
        }
    }

    ll get(int x, int y, int z){
        ll ans = 0;
        for(int i = x; i > 0; i -= i & -i){
            for(int j = y; j > 0; j -= j & -j){
                for(int k = z; k > 0; k -= k & -k){
                    ans += tree[i][j][k];
                }
            }
        }
        return ans;
    }

    ll get(int x1, int y1, int z1, int x2, int y2, int z2){
        int coord[2][3] = {{x1 - 1, y1 - 1, z1 - 1}, {x2, y2, z2}};
        ll ans = 0;
        for(int mask = 0; mask < 8; mask++){
            ll c = get(coord[GETBIT(mask, 0)][0], coord[GETBIT(mask, 1)][1], coord[GETBIT(mask, 2)][2]);
            if(__builtin_popcount(mask) & 1) ans += c;
            else ans -= c;
        }
        return ans;
    }
};

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int tt; cin >> tt;
    while(tt--){
        int n, m; cin >> n >> m;
        for(int i= 0; i<=n; ++i) for(int j = 0; j <= n; ++j) for(int k = 0; k <= n; ++k) 
            a[i][j][k] = 0;
        BIT3D bit(n);
        while(m--){
            string t; cin >> t;

            if(t == "UPDATE"){
                int x, y, z, c; cin >> x >> y >> z >> c;
                ll diff = c - a[x][y][z];
                a[x][y][z] += diff;
                bit.upd(x, y, z, diff);
            }
            else{
                int x1, y1, z1, x2, y2, z2;
                cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
                cout << bit.get(x1, y1, z1, x2, y2, z2) << '\n';
            }
        }
    }
    
    return 0;
}

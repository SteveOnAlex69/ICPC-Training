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

const int MAX = 3e3 + 10;

int n, k;
int X[MAX], Y[MAX], pos[MAX][MAX];
vector<int> coorX[MAX], coorY[MAX];

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> k;
    vector<array<int, 3>> arr;
    vector<int> tmp;
    for(int i = 1; i <= k; i++){
        int x, y, z; cin >> x >> y >> z;
        arr.push_back({x, y, z});
        tmp.push_back(x);
        tmp.push_back(y);
        tmp.push_back(z);
    }
    remove_dup(tmp);

    ll ans = 0;

    for(auto &o: arr){
        int x = lower_bound(ALL(tmp), o[0]) - tmp.begin();
        int y = lower_bound(ALL(tmp), o[1]) - tmp.begin();
        int z = lower_bound(ALL(tmp), o[2]) - tmp.begin();
        if(z == 0){
            X[x]++;
            Y[y]++;
            pos[x][y]++;
            ans += n;
        }
        if(x == 0){
            coorY[z].push_back(y);
        }
        if(y == 0){
            coorX[z].push_back(x);
        }
    }

    for(int p = 0; p < MAX; p++){
        ans += 1LL * n * (sz(coorX[p]) + sz(coorY[p])) - 1LL * sz(coorX[p]) * sz(coorY[p]);
        for(int x: coorX[p]) ans -= X[x];
        for(int y: coorY[p]) ans -= Y[y];
        for(int x: coorX[p]) for(int y: coorY[p]){
            ans += pos[x][y];
        }
    }

    cout << ans << '\n';

    return 0;
}

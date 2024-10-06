#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1LL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
#define block_of_code if(true)
 
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
ll gcd(ll a, ll b){return __gcd(a, b);}
 
int pop_cnt(ll mask){return __builtin_popcountll(mask);}
int ctz(ull mask){return __builtin_ctzll(mask);}
int logOf(ull mask){return 63 - __builtin_clzll(mask);}
ll LASTBIT(ll mask){return (mask) & (-mask);}
ll FIRSTBIT(ll mask){return MASK(logOf(mask));}
 
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return l + (ull) rng() % (r - l + 1);}
 
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

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    clock_t start = clock();

    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int i= 0; i< n; ++i) cin>> a[i];
    sort(ALL(a));

    int ma = 0;
    while(m--){
        int x, y, z; cin >> x >> y >> z;
        if (z <= 0) continue;
        int j = 0, k = 0;
        ll sum = 0;
        for(int i = 0; i< n; ++i){
            while(a[i] - a[j] >= x) j++;
            while(a[i] - a[k] > y) k++;
            sum += j - k;
            if (sum >= z){
                maximize(ma, a[i]);
                break;
            }
        }
        if (sum < z){
            cout << -1 << "\n";
            return 0;
        }
    }
    cout << ma << "\n";

    cerr << "Time elapsed: " << clock() - start << " ms!\n";
    return 0;
}

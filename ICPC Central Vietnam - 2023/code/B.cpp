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

const int N = 105;

const int MOD = 2023;
int dp[N][N][N];
vector<int> adj[N];

void add(int &a, int b){
    a += b;
    if (a >= MOD) a -= MOD;
}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    clock_t start = clock();

    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i<n; ++i) cin >> a[i];
    sort(ALL(a));

    for(int i = 0; i<n; ++i) for(int j = i + 1; j < n; ++j) if (gcd(a[i], a[j]) == 1) 
        adj[i].push_back(j);


    for(int i = 0; i < n; ++i) dp[1][i][i] = 1;

    for(int k = 1; k <= n; ++k) for(int i= 0; i<n; ++i) for(int j = i; j < n; ++j) if (dp[k][i][j]){
        for(int t: adj[j]) add(dp[k+1][i][t], dp[k][i][j]);
    }

    int q; cin >> q;
    while(q--){
        int s, t, k; cin >> s >> t >> k;
        s = lower_bound(ALL(a), s) - a.begin();
        t = lower_bound(ALL(a), t) - a.begin();

        cout << dp[k+1][s][t] << "\n";
    }

    cerr << "Time elapsed: " << clock() - start << " ms!\n";
    return 0;
}

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1LL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
 
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
 
ll LASTBIT(ll mask){return (mask) & (-mask);}
int pop_cnt(ll mask){return __builtin_popcountll(mask);}
int ctz(ll mask){return __builtin_ctzll(mask);}
int logOf(ll mask){return 63 - __builtin_clzll(mask);}
 
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
    void printArr(T& container, char separator = ' ', char finish = '\n'){
        for(auto item: container) cout << item << separator;
        cout << finish;
    }
 
template <class T>
    void remove_dup(vector<T> &a){
        sort(ALL(a));
        a.resize(unique(ALL(a)) - a.begin());
    }

const int N = 1010;
const int INF = 1e9 + 69;

int n, m;
string s[N];
int dp[N][MASK(10)];

int continuous_cnt[MASK(10)];
int diff[MASK(10)][MASK(10)];

struct P{
    int i, w;
    P(){}
    P(int i, int w): i(i), w(w){}
};

struct compare{
    bool operator () (P a, P b){
        return a.w > b.w;
    }
};
 
int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> m;
    for(int i = 0; i<n; ++i) cin >> s[i];

    for(int mask = 0; mask < MASK(m); ++mask){
        continuous_cnt[mask] = pop_cnt(mask);
        for(int i = 1; i < m; ++i) if (GETBIT(mask, i) && GETBIT(mask, i-1))
            continuous_cnt[mask]--;
    }
    for(int mask1 = 0; mask1 < MASK(m); ++mask1)
    for(int mask2 = 0; mask2 < MASK(m); ++mask2){
        for(int i = 0; i < m; ++i) if (GETBIT(mask2, i) && !GETBIT(mask1, i))
            diff[mask1][mask2]++;
    }

    for(int i = 0; i<=n; ++i) for(int j = 0; j < MASK(m); ++j) dp[i][j] = INF;
    dp[0][0] = 0;
    for(int i = 0; i<n; ++i){
        int cur_layer = 0;
        for(int j = 0; j < m; ++j) if (s[i][j] == '#') cur_layer += MASK(j);

        priority_queue<P, vector<P>, compare> pq;
        for(int j = 0; j < MASK(m); ++j) if (dp[i][j] != INF) pq.push(P(j, dp[i][j]));
        while(pq.size()){
            P u = pq.top(); pq.pop();
            for(int j = 0; j < m; ++j) {
                int cost = u.w + (GETBIT(u.i, j) == 0);
                if (minimize(dp[i][u.i ^ MASK(j)], cost))
                    pq.push(P(u.i ^ MASK(j), cost));
            }
        }

        for(int j = cur_layer; j >= 0; j = (j - 1) & cur_layer) if (dp[i][j] != INF){
            int cost = continuous_cnt[cur_layer - j] + dp[i][j];
            minimize(dp[i+1][j], cost);
            if (j == 0) break;
        }
    }

    int ans = INF;
    for(int mask = 0; mask < MASK(m); ++mask) minimize(ans, dp[n][mask]);
    cout << ans << "\n";
 
    return 0;
}

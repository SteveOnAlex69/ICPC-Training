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

    // freopen("input.inp", "r", stdin);
    // int n, m; cin >> n >> m;
    // vector<string> board(n);
    // for(int i = 0; i < n; i++) cin >> board[i];
    // int cntZero = 0, cntEdge = 0;
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < m; j++) if(board[i][j] == '.'){
    //         cntZero += (board[i][j] == '.');
    //         if(i + 1 < n && board[i + 1][j] == '.') cntEdge++;
    //         if(j + 1 < m && board[i][j + 1] == '.') cntEdge++;
    //     }
    // }
    // // cout << cntZero << ' ' << cntEdge << '\n';

    // cout << 1LL * cntZero * (cntZero - 1) - cntEdge * 2 << '\n';

    const int MOD = 1e9 + 7;

    int T; cin >> T;
    while(T--){
        int n; cin >> n;
        vector<int> old_dp(80, 0), new_dp(80, 0);
        new_dp[0] = 1;
        for(int i = 1; i <= n; i++){
            int c; cin >> c;
            for(int j = 0; j <= 70; j++){
                old_dp[j] = new_dp[j];
                new_dp[j] = 0;
            }
            for(int j = 0; j <= 70; j++){
                //choose
                new_dp[j] += old_dp[j];
                if(new_dp[j] >= MOD) new_dp[j] -= MOD;
                new_dp[__gcd(j, c)] += old_dp[j];
                if(new_dp[__gcd(j, c)] >= MOD) new_dp[__gcd(j, c)] -= MOD;
            }
        }

        ll ans = 0;
        for(int i = 1; i <= 70; i++){
            ans += 1LL * i * new_dp[i] % MOD;
            if(ans >= MOD) ans -= MOD;
        }

        cout <<ans << '\n';
    }

    cerr << "Time elapsed: " << clock() - start << " ms!\n";
    return 0;
}

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


struct KMP{
    struct Node{
        array<int, 2> nxt;
        int pi;
        Node(){nxt[0] = nxt[1] = 0;pi = -1;}
    };

    int n;
    vector<Node> a;

    KMP(string s){
        n = s.size();
        a.resize(n+1);
        s = "#" + s;
        for(int i = 0; i<n; ++i){
            if (i < n){
                a[i + 1].pi = a[i].nxt[s[i+1] - '0'];
                a[i].nxt[s[i+1] - '0'] = i + 1;
                a[i+1].nxt = a[a[i + 1].pi].nxt;
            }
        }
    }

    int get_nxt(int i, int digit){
        return a[i].nxt[digit];
    }

    int count_matches(string s){
        if (s.size() < n) return 0;
        int x = 0;
        int ans = 0;
        for(char c: s){
            x = a[x].nxt[c - '0'];
            if (x == n) ans++;
        }
        return ans;
    }
};

const int N = 2020, K = 11;
const int INF = 1e4 + 69;
short dp[N][N][K];
pair<short, short> parent[N][N][K];
bool digit[N][N][K];

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    clock_t start = clock();

    int n, m, d; cin >> n >> m >> d;
    vector<int> a(n+1), b(n+1);
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for(int i = 1; i <= n; ++i) cin >> b[i];
    string s; cin >> s;
    for(char &c: s){
        if (c == 'R') c = '0';
        else c = '1';
    }

    for(int i = 0; i <= n; ++i) for(int j = 0; j <= n; ++j) for(int k = 0; k <= m; ++k) 
        dp[i][j][k] = -INF;

    dp[0][0][0] = 0;
    KMP kkk(s);
    for(int i = 0; i < n; ++i) for(int j = 0; j <= i; ++j) for(int k = 0; k <= m; ++k) if (dp[i][j][k] != -INF){
        short cu = dp[i][j][k];
        if (maximize(dp[i + 1][j + 1][kkk.get_nxt(k, 0)], cu + (kkk.get_nxt(k, 0) == m))) {
            digit[i + 1][j + 1][kkk.get_nxt(k, 0)] = 0;
            parent[i + 1][j + 1][kkk.get_nxt(k, 0)] = {j, k};
        }
        if (maximize(dp[i + 1][j][kkk.get_nxt(k, 1)], cu + (kkk.get_nxt(k, 1) == m))){
            digit[i + 1][j][kkk.get_nxt(k, 1)] = 1;
            parent[i + 1][j][kkk.get_nxt(k, 1)] = {j, k};
        }
    }

    ll ans = -1e18;
    pair<int, int> cur = {-1, -1};
    for(int j = 0; j <= n; ++j) for(int k = 0; k <= m; ++k) if (dp[n][j][k] != -INF){
        if (maximize(ans, 1LL * dp[n][j][k] * d - a[j] - b[n - j]))
            cur = {j, k};
    }
    cout << ans << "\n";

    string res;
    for(int i = n; i>=1; --i){
        if (digit[i][cur.first][cur.second] == 0) res.push_back('R');
        else res.push_back('B');

        cur = parent[i][cur.first][cur.second];
    }
    reverse(ALL(res));
    cout << res << "\n";


    cerr << "Time elapsed: " << clock() - start << " ms!\n";
    return 0;
}

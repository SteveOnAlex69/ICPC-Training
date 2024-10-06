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
ll lcm(ll a, ll b){return a / gcd(a, b) * b;}
 
ll LASTBIT(ll mask){return (mask) & (-mask);}
int pop_cnt(ll mask){return __builtin_popcountll(mask);}
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

const int N = 509, M= 1e4 + 69;
const int INF = 1e9 + 69;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int subtask; 
int n, g;
int a[N][N];
int dp[N][N];
bool visited[N][N];
vector<pair<int, int>> st[M];

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> subtask; 
    if (subtask == 1){
        cin >> n >> g;
        for(int i= 1; i<=n; ++i)for(int j = 1; j<=n; ++j) cin >> a[i][j];

        for(int i = 1; i<=n; ++i) for(int j= 1; j<=n; ++j) dp[i][j] = INF;
        memset(visited, 0, sizeof visited);
        dp[1][1] = (a[1][1] < g);
        deque<pair<int, int>> q; q.push_back({1, 1});
        while(q.size()){
            pair<int, int> u = q.front(); q.pop_front();
            if (visited[u.first][u.second]) continue;
            visited[u.first][u.second] = true;
            for(int d = 0; d < 4; ++d){
                pair<int, int> v = {u.first + dx[d], u.second + dy[d]};
                if (minimize(dp[v.first][v.second], dp[u.first][u.second] + (a[v.first][v.second] < g))){
                    if (a[v.first][v.second] < g) q.push_back(v);
                    else q.push_front(v);
                }
            }
        }
        cout << dp[n][n] << "\n";
    }
    else{
        cin >> n;
        for(int i= 1; i<=n; ++i)for(int j = 1; j<=n; ++j) cin >> a[i][j];

        dp[1][1] = a[1][1];
        st[a[1][1]].push_back({1, 1});
        for(int w = M - 1; w >= 1; --w){
            while(st[w].size()){
                pair<int, int> u = st[w].back(); st[w].pop_back();
                if (dp[u.first][u.second] > w) continue;
                for(int d = 0; d < 4; ++d){
                    pair<int, int> v = {u.first + dx[d], u.second + dy[d]};
                    int nxt_w = min(w, a[v.first][v.second]);
                    if (maximize(dp[v.first][v.second], nxt_w)){
                        st[nxt_w].push_back(v);
                    }
                }

            }
        }
        cout << dp[n][n] << "\n";
    }

    return 0;
}

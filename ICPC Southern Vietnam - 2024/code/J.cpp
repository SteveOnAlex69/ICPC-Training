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
 
const long N = 2e5 + 69;
const int MOD = 1e9 + 7;
 
long pref[N][52];

int convert(char c){
    if (c >= 'a' && c <= 'z') return c - 'a';
    return c - 'A' + 26;
}
 
int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
    int n; cin >> n;
    string s; cin >> s;

    ll mask = 0;
    for(char c: s) mask |= MASK(convert(c));
 
    long distinct = pop_cnt(mask);
 
    s = "0" + s;
    for(long i= 1; i<=n; ++i){
        for(long j = 0; j<52; ++j) pref[i][j] = pref[i-1][j];
        pref[i][convert(s[i])]++;
    }
 
    vector<vector<long>> nimba;
    for(long i=0; i<=n; ++i){
        for(long j = 0; j<52; ++j) pref[i][j] = pref[i][j] * distinct - i;
        vector<long> cur;
        for(long j = 0; j<52; ++j) if (GETBIT(mask, j))
            cur.push_back(pref[i][j]);
        nimba.push_back(cur);
    }
    sort(ALL(nimba));
    ll ans = 0;
    long cur = 0;
    for(long i= 1; i<=n; ++i){
        if (nimba[i] == nimba[i-1]) cur++;
        else cur = 0;
        ans += cur;
    }
    ans %= MOD;
    cout << ans << "\n";
 
    return 0;
}

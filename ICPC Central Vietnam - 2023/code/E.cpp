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

    int n; cin >> n;

    string ans;
    for(int j = 0; j < n; ++j){
        string cu;
        for(int k = 0; k < MASK(n); ++k) if (GETBIT(k, j)) cu += "[" + to_string(k+1) + "]+";
        cu.pop_back();
        cu = "(" + cu + ")";
        cu += "%2";
        if (MASK(j) > 1)
            cu += "*" + to_string(MASK(j));
        ans += cu + "+";
    }
    ans.pop_back();
    for(int i = 0; i < MASK(n); ++i)
        cout << ans + "=" + to_string(i) << "\n";
    cout.flush();

    int t; cin >> t;
    while(t--){
        vector<int> state(MASK(n));
        for(int i= 0; i < MASK(n); ++i) cin >> state[i];

        int c_pos; cin >> c_pos;
        c_pos--;
        for(int i= 0; i < MASK(n); ++i) if (state[i]) c_pos ^= i;

        cout << c_pos + 1 << endl;

        string verdict; cin >> verdict;
        if (verdict == "BAD") break;
    }

    cerr << "Time elapsed: " << clock() - start << " ms!\n";
    return 0;
}

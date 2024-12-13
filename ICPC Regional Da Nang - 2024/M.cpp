#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

//mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng(1);
ll rngesus(ll l, ll r){return (ull) rng() % (r - l + 1) + l;}

#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

ll gcd(ll a, ll b){return __gcd(a, b);}
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
int pop_cnt(ull mask){return __builtin_popcountll(mask);}
int ctz(ull mask){return __builtin_ctzll(mask);}
int logOf(ull mask){return 63 - __builtin_clzll(mask);}

template <class T1, class T2>
    bool maximize(T1 &a, T2 b){
        if (a < b){a = b; return true;}
        return false;
    }
template <class T1, class T2>
    bool minimize(T1 &a, T2 b){
        if (a > b){a = b; return true;}
        return false;
    }
template <class T>
    void printArr(T &a){
        for (auto i: a) cout << i << " ";
        cout << "\n";
    }
template <class T>
    void remove_dup(vector<T> &a){
        sort(ALL(a));
        a.resize(unique(ALL(a)) - a.begin());
    }

//int n;
//string s;
//int i;
//int query_cnt = 0;
//
//void init_checker(){
////    cin >> n;
////    cin >> s;
//    n = rngesus(1, 555);
//    s = string(n, '0');
//    for(char &c: s) c += rngesus(0, 1);
//    i = 0;
//    query_cnt = 0;
//}

int get_ans(){
//    return s[i] - '0';
    int verdict; cin >> verdict;
    return verdict;
}

void go_left(int y){
    cout << "< " << y << endl;
//    query_cnt++;
//    s[i] = y + '0';
//    i = (i + n - 1) % n;
}
void go_right(int y){
    cout << "> " << y << endl;
//    query_cnt++;
//    s[i] = y + '0';
//    i = (i + 1) % n;
}
void answer(int y){
    cout << "! " << y << endl;

}

const int L = 27;

void solve(){
//    init_checker();
    string troll(L, '0');
    for(int i = 0; i < L-1; ++i) troll[i] += rngesus(0, 1);

    for(int i = 0; i < L-1; ++i) {
        get_ans();
        go_right(1);
    }
    get_ans();
    go_left(troll[L-1] - '0');

    for(int i = L-2; i >= 0; --i){
        int cur = get_ans();
        if (cur == 0) {
            answer(L-1 - i);
            return;
        }
        go_left(troll[i] - '0');
    }

    string cur = troll;
    for(int i = 1; ; ++i){
        int cu = get_ans();
        cur = string(1, '0' + cu) + cur;
        cur.pop_back();
        if (cur == troll) {
            answer(i);
            return;
        }
        go_left(cu);
    }

}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//    freopen("input.inp", "r", stdin);

    int t; cin >> t;
    while(t--) solve();

    return 0;
}

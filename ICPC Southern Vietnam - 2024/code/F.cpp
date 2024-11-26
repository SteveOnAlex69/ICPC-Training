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

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int C, N, M, L;
    cin >> C >> N >> M >> L;

    int numInvalid[2] = {0, 0};

    set<int> st[2];
    for(int i = 0; i < M * 2; i++){
        int x; cin >> x;
        x++;

        if(x + L - 1 > N){
            numInvalid[i & 1]++;
            continue;
        }

        auto it1 = st[!(i & 1)].lower_bound(x);
        auto it2 = st[!(i & 1)].upper_bound(x);

        if(it1 != st[!(i & 1)].end() && *it1 <= x + L){
            numInvalid[i & 1]++;
            continue;
        }

        if(it2 != st[!(i & 1)].begin()){
            it2--;
            if(*it2 >= x - L){
                numInvalid[i & 1]++;
                continue;            
            }
        }

        st[i & 1].insert(x);
    }

    if(C == 1){
        cout << numInvalid[0] << ' ' << numInvalid[1] << '\n';
        return 0;
    }

    for(int i = 0; i < 2; i++){
        vector<int> ord;
        for(auto it: st[i]) ord.push_back(it);
        ord.push_back(N * 2);
        int cur = 0, ans = 0;
        for(int i = 0; i + 1 < sz(ord); i++){
            cur += min(L, ord[i + 1] - ord[i]);
            if(ord[i + 1] - ord[i] > L){
                maximize(ans, cur);
                cur = 0;
            }
        }

        cout << ans << ' ';
    }
    
    return 0;
}

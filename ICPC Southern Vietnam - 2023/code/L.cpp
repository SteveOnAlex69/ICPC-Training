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

ll n, m, x, y, k; 

ll get_pos(ll k){
    if (k <= 3){
        return 1 + (k - 1) * 2;
    }
    ll sigma = get_pos(k - 3);
    if (sigma >= 1) sigma++;
    if (sigma >= 3) sigma++;
    if (sigma >= 5) sigma++;
    return sigma;
}

ll get_pos_better(ll k){
    if (k <= 10) return get_pos(k);
    if (k % 3 == 1){
        return k - 3;
    }
    else if (k % 3 == 2){
        return 1 + k;
    }
    else{
        return 2 + k;
    }
}

ll dis(pair<ll, ll> a, pair<ll, ll> b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}

ll sqr(ll x){return x * x;}
ll triangle(ll x){
    return x * (x + 1) / 2;
}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> m >> x >> y >> k;
    k = get_pos_better(k);

    if (k == n * m){
        cout << 0 << "\n";
        return 0;
    }

    ll l = 0, r = n + m;
    while(l < r){
        ll mid = (l + r + 1) >> 1;
        ll sum = sqr(mid + 1) + sqr(mid);

        // bottom
        if (x - mid <= 0) {
            sum -= sqr(x - mid - 1);
        }
        // top
        if (x + mid > n){
            sum -= sqr(x + mid - n);
        }
        // left
        if (y - mid <= 0){
            sum -= sqr(y - mid - 1);
        }
        // right
        if (y + mid > m){
            sum -= sqr(y + mid - m);
        }

        // bottom left
        if (dis({0, 0}, {x,y}) <= mid){
            ll d = dis({0, 0}, {x,y});
            sum += triangle(mid - d + 1);

        }
        // bottom right
        if (dis({0, m+1}, {x,y}) <= mid){
            ll d = dis({0, m+1}, {x,y});
            sum += triangle(mid - d + 1);
        }

        // top left
        if (dis({n+1, 0}, {x,y}) <= mid){
            ll d = dis({n+1, 0}, {x,y});
            sum += triangle(mid - d + 1);
        }

        // top right
        if (dis({n+1, m+1}, {x,y}) <= mid){
            ll d = dis({n+1, m+1}, {x,y});
            sum += triangle(mid - d + 1);
        }

        sum = n * m - sum;
        if (sum <= k - 1) r = mid - 1;
        else l = mid;
    }

    cout << l + 1 << "\n";

    // for(int n = 1; n <= 1000; ++n){
    //     if (get_pos(n) != get_pos_better(n)){
    //         cout << "Brun\n";
    //         cout << n << " " << get_pos(n) << " " << get_pos_better(n) << "\n";
    //     }
    // }

    return 0;
}

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
 
template <class T1, class T2>
    bool maximize(T1 &a, T2 b){
        if (a < b) {a = b; return true;}
        return false;
    }
 
const ll INF = 1e18 + 69;

int sign(ll x){
    return (x > 0) - (x < 0);
}

void solve(){
    int n, k; cin >> n >> k;
    vector<ll> a(k*2+2);
    a.back() = n;
    for(int i = 1; i <= k * 2; ++i) cin >> a[i];

    vector<pair<ll, ll>> range;
    for(int i = 0; i < (int)a.size(); i += 2) 
        if (a[i] < a[i+1]) 
            range.push_back({a[i] * 2, a[i + 1] * 2});

    ll ans_init = 0;
    for(pair<ll, ll> i: range) ans_init += i.second - i.first;

    if (ans_init == 0){
        cout << 0 << "\n";
        return;
    }

    int m = range.size();
    vector<int> slope_changing_points;
    for(int i = 0; i < m; ++i){
        int cur_len = range[i].second - range[i].first;
        for(int j = i; j < m - 1; ++j){
            int L = range[j].second, R = range[j+1].first;

            slope_changing_points.push_back(L - range[i].second + 1);
            slope_changing_points.push_back(-(L - range[i].second + cur_len) -1);

            slope_changing_points.push_back(-(R - range[i].second) - 1);
            slope_changing_points.push_back(R - range[i].second + cur_len + 1);
        }
        slope_changing_points.push_back(range.back().second - range[i].second + 1);
        slope_changing_points.push_back(-(range.back().second - range[i].second + cur_len) - 1);
    }

    slope_changing_points.push_back(n + 1);

    sort(ALL(slope_changing_points), [](int x, int y){return abs(x) < abs(y);});
    int cur_slope = sign(slope_changing_points[0]);   
    int sum = 0;
    int ma = 0;

    for(int i = 1; i < (int) slope_changing_points.size(); ++i){
        ll prev = abs(slope_changing_points[i-1]), cur = abs(slope_changing_points[i]);
        sum += 1LL * (cur - prev) * cur_slope;
        cur_slope += sign(slope_changing_points[i]);

        maximize(ma, sum);
        if (slope_changing_points[i] == n + 1) break;
    }


    cout << ans_init + ma << "\n";
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

    freopen("ROAI.INP", "r", stdin);
    freopen("ROAI.OUT", "w", stdout);

    clock_t start = clock();

    solve();

    cerr << "Time elapsed: " << clock() - start << " ms\n";
    return 0;
}
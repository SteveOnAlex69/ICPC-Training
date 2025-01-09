#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
 
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
ll gcd(ll a, ll b){return __gcd(a, b);}
ll lcm(ll a, ll b){return a / gcd(a, b) * b;}
 
ll LASTBIT(ll mask){return (mask) & (-mask);}
int pop_cnt(ull mask){return __builtin_popcountll(mask);}
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

struct FastIO{
    string buffer;
    vector<ll> king;
    void init(ll _n = 0){
        getline(cin, buffer, '\0');
        buffer += "\n";
        king.reserve(_n);
        ll cur = 0;
        for(char c: buffer){
            if (c <= '9' && c >= '0'){
                if (cur == -1) cur = 0;
                cur = cur * 10 + (c - '0');
            }
            else{
                if (cur != -1) king.push_back(cur);
                cur = -1;
            }
        }
        
        reverse(ALL(king));
    }
    
    template <class T>
    FastIO& operator >> (T &x){
        x = 0;
        if (king.empty()) return *this;
        x = king.back(); king.pop_back();
        return *this;
    }

    bool isEmpty(){return king.empty();}
};

FastIO fin;

const int N = 5e5 + 69;

struct LinkedList{
    struct Node{
        int prev, nxt;
        Node(){prev = nxt = -1;}
    };
    vector<Node> a;
    LinkedList(int n){
        a.reserve(n);
        a.emplace_back();
    }

    int insert_behind(int i){
        int j = a.size();
        a.emplace_back();
        if (a[i].nxt == -1){
            a[i].nxt = j;
            a[j].prev = i;
        }
        else{
            int k = a[i].nxt;
            a[i].nxt = a[k].prev = j;
            a[j].prev = i;
            a[j].nxt = k;
        }
        return j;
    }

    vector<int> get_arr(){
        vector<int> ans;
        int i = 0;
        while(i != -1){
            ans.push_back(i);
            i = a[i].nxt;
        }
        return ans;
    }
};

struct Trie{
    struct Node{
        int sum;
        int child[2];
        Node(){
            sum = 0;
            memset(child, -1, sizeof child);
        }
    };

    vector<Node> a;

    Trie(int n = 0){
        a.reserve(n);
        a.emplace_back();
    }

    void add_child(int &x){
        x = a.size();
        a.emplace_back();
    }

    void apply(int id, int val, int node_sz){
        a[id].sum = val * node_sz;
    }

    void down(int id, int node_sz){
        for(int i = 0; i <= 1; ++i) {
            if (a[id].child[i] == -1) add_child(a[id].child[i]);
            apply(a[id].child[i], a[id].sum == node_sz, node_sz >> 1);
        }
    }

    void update(int u, int v, int val, int l, int r, int id){
        if (u <= l && r <= v){
            apply(id, val, r - l + 1);
            return;
        }
        if (a[id].sum == 0|| a[id].sum == r - l + 1) down(id, r - l + 1);
        int mid = (l + r) >> 1;
        if (u <= mid) {
            if (a[id].child[0] == -1) add_child(a[id].child[0]);
            update(u, v, val, l, mid, a[id].child[0]);
        }
        if (v > mid) {
            if (a[id].child[1] == -1) add_child(a[id].child[1]);
            update(u, v, val, mid + 1, r, a[id].child[1]);
        }
        a[id].sum = 0;
        if (a[id].child[0] != -1) 
            a[id].sum += a[a[id].child[0]].sum;
        if (a[id].child[1] != -1) 
            a[id].sum += a[a[id].child[1]].sum;
    }

    void update(int u, int v, int val){
        update(u, v, val, 0, MASK(30) - 1, 0);
    }

    int get_index(int val){
        int id = 0;
        int l = 0, r = MASK(30) - 1;
        while(l < r){
            int mid = (l + r) >> 1;
            if (a[id].sum == 0|| a[id].sum == r - l + 1) down(id, r - l + 1);
            if (a[id].child[0] != -1){
                if (a[a[id].child[0]].sum >= val){
                    r = mid;
                    id = a[id].child[0];
                }
                else{
                    val -= a[a[id].child[0]].sum;
                    l = mid + 1;
                    id = a[id].child[1];
                }
            }
            else{
                l = mid + 1;
                id = a[id].child[1];
            }
        }
        return l;
    }


 
    int get_index(int u, int &val, int l, int r, int id){
        if (r < u) return -1;
        if (u <= l && val > a[id].sum){
            val -= a[id].sum;
            return -1;
        }
        if (l == r) return l;
        if (a[id].sum == 0|| a[id].sum == r - l + 1) down(id, r - l + 1);
        int mid = (l + r) >> 1;
        if (a[id].child[0] != -1){
            int cur = get_index(u, val, l, mid, a[id].child[0]);
            if (cur != -1) return cur;
        }
        return get_index(u, val, mid + 1, r, a[id].child[1]);
    }
 
    int get_index(int l, int val){
        return get_index(l, val, 0, MASK(30) - 1, 0);
    }
 
};

void doping(vector<pair<int, int>> &range, vector<int> cut_points){
    remove_dup(cut_points);
    vector<pair<int, int>> tmp;
    for(pair<int, int> i: range){
        int l = i.first, r = i.second;
        int idx = lower_bound(ALL(cut_points), l) - cut_points.begin();
        while (idx < (int)cut_points.size() && cut_points[idx] < i.second){
            tmp.push_back({l, cut_points[idx]});
            l = cut_points[idx] + 1;
            idx++;
        }
        tmp.push_back({l, r});
    }
    range = tmp;
}


struct FenwickTree{
    int n;
    vector<ll> a;

    FenwickTree(int _n){
        n = _n;
        a.resize(n+1);
    }

    void update(int i, ll v){
        while(i <= n){
            a[i] += v;
            i += LASTBIT(i);
        }
    }

    ll get(int i){
        ll ans = 0;
        while(i > 0){
            ans += a[i];
            i -= LASTBIT(i);
        }
        return ans;
    }

    ll get(int l, int r){return get(r) - get(l-1);}

    int binary_lift(ll x){
        int p = MASK(logOf(n)), idx =0;
        while(p > 0){
            if (idx + p <= n && x > a[idx + p]){
                idx += p;
                x -= a[idx];
            }
            p >>= 1;
        }
        return idx + 1;
    }
};

ll sum_range(ll l, ll r) {return (r + l) * (r - l + 1) / 2;}


void solve(){
    int q; fin >> q;
    vector<array<int, 3>> queries(q);
    for(int i = 0; i < q; ++i) for(int j = 0; j < 3; ++j)
        fin >> queries[i][j];
    int cur = 0;
    vector<pair<int, int>> right_points; 
    right_points.push_back({0, -1});
    for(auto i: queries){
        if (i[0] == 1){
            right_points.push_back({i[1], -1});
            right_points.push_back({cur += i[2], -1});
        }
        else if (i[0] == 2) {
            right_points.push_back({i[1], -1});
        }
    }
    remove_dup(right_points);

    LinkedList sigma(1e6);
    right_points[0].second = 0;
    int m = right_points.size();
    FenwickTree S(m); S.update(1, 1);
    cur = 0;
    for(auto i: queries){
        if (i[0] == 1){
            int x = i[1], k = i[2];
            int idx1 = lower_bound(ALL(right_points), make_pair(x, -1)) - right_points.begin();
            if (right_points[idx1].second == -1){
                int j = right_points[S.binary_lift(S.get(idx1 + 1) + 1)-1].second;
                j = sigma.a[j].prev;
                right_points[idx1].second = sigma.insert_behind(j);
                S.update(idx1 + 1, 1);
            }
            cur += k;

            int idx2 = lower_bound(ALL(right_points), make_pair(cur, -1)) - right_points.begin();
            right_points[idx2].second = sigma.insert_behind(right_points[idx1].second);   
            S.update(idx2 + 1, 1);
        }
        else if (i[0] == 2){
            int x = i[1];
            int idx1 = lower_bound(ALL(right_points), make_pair(x, -1)) - right_points.begin();
            if (right_points[idx1].second == -1){
                int j = right_points[S.binary_lift(S.get(idx1 + 1) + 1)-1].second;
                j = sigma.a[j].prev;
                right_points[idx1].second = sigma.insert_behind(j);
                S.update(idx1 + 1, 1);
            }
        }
    }

    vector<int> arr = sigma.get_arr();
    int n = arr.size();
    vector<int> pos(n);
    for(int i = 0; i < n; ++i) pos[arr[i]] = i;

    vector<pair<int,int>> range(n);
    int l = 0;
    for(auto i: right_points){
        range[pos[i.second]] = {l, i.first};
        l = i.first + 1;
    }

    vector<pair<int, int>> right_pos;
    for(int i = 0; i < n; ++i) right_pos.push_back({range[i].second, i});

    remove_dup(right_pos);
    vector<int> pref(n+1);
    for(int i = 1; i <= n; ++i) pref[i] = pref[i-1] + (range[i-1].second - range[i-1].first + 1);

    vector<int> cut_points;
    vector<pair<int, int>> big_range;
    Trie tri(40000000);
    tri.update(1, 1, 1);
    cur = 0;


    for(auto i: queries){
        big_range.push_back({});
        if (i[0] == 1){
            int k = i[2];
            int L = cur + 1, R = cur += k;
            while(L <= R) {
                pair<int,int> cur = *lower_bound(ALL(right_pos), make_pair(L, -1));
                L = cur.first + 1;
                tri.update(pref[cur.second] + 1, pref[cur.second + 1], 1);
            }
        }
        else if (i[0] == 2){
            int x = i[1], h = i[2];

            int L = pref[(*lower_bound(ALL(right_pos), make_pair(x, -1))).second+1];

            int R = tri.get_index(L + 1, h);
            tri.update(L+1, R, 0);

            int idx = lower_bound(ALL(pref), R) - pref.begin();
            cut_points.push_back(range[idx - 1].second - (pref[idx] - R));
            big_range.back() = {L, R};
        }
        else{
            int l = i[1], r = i[2];
            int R = tri.get_index(r);
            int idx = lower_bound(ALL(pref), R) - pref.begin();
            cut_points.push_back(range[idx - 1].second - (pref[idx] - R));

            int L = tri.get_index(l) - 1;
            idx = lower_bound(ALL(pref), L) - pref.begin();
            if (idx >= 1){
                cut_points.push_back(range[idx - 1].second - (pref[idx] - L));
            }

            big_range.back() = {L, R};
        }
    }
    doping(range, cut_points);

    right_pos.clear();
    pref.clear();
    n = range.size();
    for(int i = 0; i < n; ++i) right_pos.push_back({range[i].second, i});
    remove_dup(right_pos);

    pref = vector<int>(n+1);
    for(int i = 1; i <= n; ++i) pref[i] = pref[i-1] + (range[i-1].second - range[i-1].first + 1);

    FenwickTree bit(n);
    cur = 0;
    for(int it = 0; it < q; ++it){
        array<int, 3> i = queries[it];
        if (i[0] == 1){
            int k = i[2];
            int L = cur + 1, R = cur += k;
            int idx = lower_bound(ALL(right_pos), make_pair(L, -1)) - right_pos.begin();
            while(idx < n && right_pos[idx].first <= R) {
                pair<int,int> cur = right_pos[idx];
                bit.update(cur.second + 1, sum_range(range[cur.second].first, range[cur.second].second));
                idx++;
            }
        }
        else if (i[0] == 2){
            int L, R;
            tie(L, R) = big_range[it];
            int idx = lower_bound(ALL(pref), L)- pref.begin();
            ll cur = bit.get(idx);

            int cnt = 0;

            while(cnt < i[2]){
                int _idx = bit.binary_lift(cur + 1);
                cnt += range[_idx-1].second - range[_idx-1].first + 1;
                bit.update(_idx, -sum_range(range[_idx-1].first, range[_idx-1].second));
            }
        }
        else{
            int L, R;
            tie(L, R) = big_range[it];

            int idx1 = lower_bound(ALL(pref), L) - pref.begin();
            int idx2 = lower_bound(ALL(pref), R) - pref.begin();

            cout << bit.get(idx2) - bit.get(idx1) << "\n";
        }
    }

}
int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);

    freopen("TSEQ.INP", "r", stdin);
    freopen("TSEQ.OUT", "w", stdout);

    clock_t start = clock();

    fin.init(2e6);
    solve();

    cerr << "Time elapsed: " << clock() - start << " ms\n";
    return 0;
}
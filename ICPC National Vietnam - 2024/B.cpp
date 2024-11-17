#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;


mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){
    return (ull) rng() % (r - l + 1) + l;
}

ll gcd(ll a, ll b) {return __gcd(a, b);}
ll min(ll a,ll b){return (a > b)? b: a;}
ll max(ll a, ll b){return (a > b)? a: b;}

const int MOD = 998244353;
struct Modular{
    ll x;
    Modular(ll _x = 0){
        x = _x % MOD;
        if (x < 0) x += MOD;
    }

    Modular& operator += (Modular y){
        x += y.x;
        if (x > MOD) x -= MOD;
        return *this;
    }
    Modular& operator -= (Modular y){
        x -= y.x;
        if (x < 0) x += MOD;
        return *this;
    }
    Modular& operator *= (Modular y){
        x *= y.x;
        x %= MOD;
        return *this;
    }

    Modular operator + (Modular y) {
        Modular tmp = *this;
        return tmp += y;
    }
    Modular operator - (Modular y) {
        Modular tmp = *this;
        return tmp -= y;
    }
    Modular operator * (Modular y) {
        Modular tmp = *this;
        return tmp *= y;
    }
};

ostream& operator << (ostream& out, Modular x){
    out << x.x;
    return out;
}

Modular fast_pow(Modular a, ll n){
    Modular ans = 1;
    while(n){
        if (n & 1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}
Modular inverse(Modular a){return fast_pow(a, MOD - 2);}

struct DSU{
    int n;
    vector<pair<int,int>> parent;
    vector<int> sz;
    int cc, is_valid;

    vector<vector<int>> history;

    DSU(int _n){
        n = _n;
        parent.resize(n); sz.resize(n, 1);
        for(int i = 0; i < n; ++i) parent[i] = {i, 0};
        cc = n;
        is_valid = 1;
    }

    pair<int,int> find_set(int u){
        if (u == parent[u].first) return parent[u];
        pair<int,int> v = find_set(parent[u].first);
        v.second ^= parent[u].second;
        return v;
    }

    bool join_set(int x, int y, int w){
        if (check_valid() == false) return false;
        pair<int,int> u = find_set(x), v = find_set(y);
        if (u.first != v.first){
            if (sz[u.first] < sz[v.first]) swap(u, v);
            history.push_back({u.first, v.first, parent[v.first].second});
            cc--;
            sz[u.first] += sz[v.first];
            parent[v.first] = make_pair(u.first, w ^ u.second ^ v.second);
            return true;
        }
        if ((u.second ^ v.second) != w) {
            is_valid--;
            history.push_back({1});
        }
        return false;
    }

    bool check_valid(){return is_valid > 0;}
    int get_version(){return history.size();}

    void roll_back(int target_version){
        while(history.size() > target_version){
            vector<int> cur = history.back(); history.pop_back();
            if (cur.size() == 1) is_valid++;
            else{
                int u = cur[0], v = cur[1], w_v = cur[2];
                sz[u] -= sz[v];
                parent[v] = make_pair(v, w_v);
                cc++;
            }
        }
    }
};

const int N = 4e5 + 69;
struct Edge{
    int u, v, w;
    Edge(int u,int v, int w): u(u), v(v), w(w){}
};

vector<Edge> st[N * 4];

void add_edge(int u, int v, int l, int r, int id, Edge e){
    if (u > v) return;
    if (u <= l && r <= v) {
        st[id].push_back(e);
        return;
    }
    int mid = (l + r) >> 1;
    if (u <= mid) add_edge(u, v, l, mid, id * 2, e);
    if (v > mid) add_edge(u, v, mid + 1, r, id * 2 + 1, e);
}

int cap;

void dfs(int l, int r, int id, DSU &mst, Modular &ans){
    int cur_ver = mst.get_version();
    for(Edge i: st[id]) mst.join_set(i.u, i.v, i.w);
    if (mst.check_valid()){
        if (l == r){
            int cur = mst.cc;
            if (r < cap) cur--;
            ans += fast_pow(2, cur);
        }
        else{
            int mid = (l + r) >> 1;
            dfs(l, mid, id * 2, mst, ans);
            dfs(mid + 1, r, id * 2 + 1, mst, ans);
        }
    }
    mst.roll_back(cur_ver);
}

Modular solve(){
    int w, h, n; cin >> w >> h >> n;
    w++, h++;
    vector<Edge> edges;
    for(int i = 0; i < n; ++i){
        int u, v, x, y; cin >> u >> v >> x >> y;
        if (u == x && v == y) continue;
        else if (u == x){
            edges.push_back({u, u, 1});
        }
        else if (v == y) {
            edges.push_back({v + w, v + w, 1});
        }
        else{
            if (u > x) {
                swap(u, x);
                swap(v, y);
            }
            edges.push_back({u, x, 1});
            edges.push_back({v + w, y + w, 1});
            if (v > y){
                edges.push_back({u, v + w, 0});
                edges.push_back({u, y + w, 1});
                edges.push_back({x, v + w, 1});
                edges.push_back({x, y + w, 0});
            }
            else{
                edges.push_back({u, v + w, 1});
                edges.push_back({u, y + w, 0});
                edges.push_back({x, v + w, 0});
                edges.push_back({x, y + w, 1});
            }
        }
    }
    DSU mst(w + h);
    Modular ans = 0;

    for(int i = 0; i < (w + h + 1) * 4; ++i) st[i].clear();

    for(Edge &i: edges){
        if (i.u > i.v) swap(i.u, i.v);
        add_edge(0, i.u - 1, 0, w + h, 1, i);
        add_edge(i.u + 1, i.v - 1, 0, w + h, 1, i);
        add_edge(i.v + 1, w + h, 0, w + h, 1, i);
    }

    cap = w + h;
    dfs(0, w + h, 1, mst, ans);
    return ans;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) cout << solve() << "\n";


    return 0;
}

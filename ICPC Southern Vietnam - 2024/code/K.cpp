#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define ll long long
#define el '\n'
#define fu(i,a,b) for(int i = (a), _b = (b); i <= _b; ++i)
#define fd(i,a,b) for(int i = (a), _b = (b); i >= _b; --i)
#define fa(x, a) for(auto x : a)
#define re(i, n) fu(i,0,n - 1)
#define vi vector<int>
#define vvi vector<vi>
#define vll vector<ll>
#define vvll vector<vll>
#define pb push_back
#define pf push_front
#define pof pop_front
#define pob pop_back
#define sz(a) (int)(a.size())
#define all(a) a.begin(), a.end()
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define vpll vector<pll>
#define vvpll vector<vpll>
#define MP make_pair
#define fi first
#define se second
#define MASK(i) (1LL << (i))
#define db double
#define ld long double

using namespace std;

const int maxn = 1e5;
const int lim  = 1e6;
const ll  inf  = 1e16;
const ll  mod  = 1e9 + 7; /// 1007050321
const ll  base = 33137;

template<class T1,class T2>
bool maximize(T1 &a,T2 b){
    if(a < b){
        a = b;
        return 1;
    }
    return 0;
}

template<class T1,class T2>
bool minimize(T1 &a,T2 b){
    if(a > b){
        a = b;
        return 1;
    }
    return 0;
}

template<class T1,class T2>
void Add(T1 &a,T2 b){
    a += b;
    if(a >= mod) a -= mod;
    if(a < 0) a += mod;
    return;
}

template<class T1>
void compress(vector<T1> &a){
    sort(all(a));
    a.resize(unique(all(a)) - a.begin());
    return;
}

bool takeBit(ll th,ll n){return ((n >> th) & 1LL);}

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch(). count());
#define rand rd

ll ran(ll lo,ll hi){
    return (lo + rand() % (hi - lo + 1));
}

//int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
//int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

const int maxPac = 1e4;

int n,Pac,t;
pair<pii, int> pacman[maxPac + 5];
pair<char,int> quest[maxn + 5];

struct lmao {
    int nor, eas, sou, wes, dir;

    lmao() = default;

    void move(int len){
        if(dir == 1) nor += len;
        if(dir == 2) eas += len;
        if(dir == 3) sou += len;
        if(dir == 4) wes += len;
        return;
    }

    void rotate(int _time){
        dir += _time;
        if(dir > 4) dir -= 4;
        return;
    }
} change[5];

int dir[maxn + 5][5];

void solve(){
    fu(i,1,4) dir[0][i] = i;
    int pos_tele = 0;
    fu(i,1,t){
        char type;
        int val;
        cin>>type>>val;
        quest[i] = MP(type, val);
        fu(j,1,4) dir[i][j] = dir[i - 1][j];
        if(type == 'R') fu(j,1,4){
            int nj = dir[i - 1][j] + val;
            if(nj > 4) nj -= 4;
            dir[i][j] = nj;
        }
        if(type == 'Z') pos_tele = i;
    }
    fu(i,1,4) change[i].dir = i;
    fu(i,pos_tele + 1,t){
        assert(quest[i].fi != 'Z');
        if(quest[i].fi == 'A') fu(j,1,4) change[j].move(quest[i].se);
        else fu(j,1,4) change[j].rotate(quest[i].se);
    }
    fu(i,1,Pac){
        if(pos_tele){
            int x = quest[pos_tele].se / n, y = quest[pos_tele].se % n;
            pacman[i].fi = MP(x, y);
            pacman[i].se = dir[pos_tele][pacman[i].se];
        }
        int j = pacman[i].se;
        int x = pacman[i].fi.fi, y = pacman[i].fi.se;
        x = x + change[j].sou - change[j].nor;
        y = y + change[j].eas - change[j].wes;
        x %= n; y %= n;
        if(x < 0) x += n;
        if(y < 0) y += n;
        cout<<x<<' '<<y<<el;
    }
    return;
}

void input(){
    cin>>n>>Pac>>t;
    fu(i,1,Pac) cin>>pacman[i].fi.fi>>pacman[i].fi.se>>pacman[i].se;
    return;
}

int main(){
    fast
//    freopen("input.inp", "r", stdin);
//    freopen("output.out", "w", stdout);
    input();
    solve();
    return 0;
}

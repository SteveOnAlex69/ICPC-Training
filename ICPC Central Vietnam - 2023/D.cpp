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

int nRow, nCol, bomb;
vector<vi> a;

bool check(int len){
    int cnt = 0;
    fu(i,1,nRow){
        int remain = 0;
        fu(j,1,nCol){
            if(a[i][j] == 0) if(remain) --remain;
            if(a[i][j] == 1){
                if(remain) --remain;
                else{
                    ++cnt;
                    remain = (len << 1);
                }
            }
            if(a[i][j] == 2) remain = 0;
        }
    }
    return (cnt <= bomb);
}

void solve(){
    int lo = 0, hi = nCol + 1;
    while(lo < hi){
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout<<(hi <= nCol ? hi : -1);
    return;
}

void input(){
    cin>>nRow>>nCol>>bomb;
    a.resize(nRow + 5);
    fu(i,1,nRow) a[i].resize(nCol + 5);
    fu(i,1,nRow){
        string s;
        cin>>s;
        fu(j,1,nCol){
            if(s[j - 1] == '.') a[i][j] = 0;
            else if(s[j - 1] == 'x') a[i][j] = 1;
            else a[i][j] = 2;
        }
    }
    return;
}

int main(){
    fast
//    freopen("planting.in", "r", stdin);
//    freopen("planting.out", "w", stdout);
    input();
    solve();
    return 0;
}

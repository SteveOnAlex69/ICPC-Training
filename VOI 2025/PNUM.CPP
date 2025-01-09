#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
 
const ll MOD = 1e9 + 7;
struct Modular{
    ll x;
    Modular(ll _x = 0){
        x = _x % MOD;
        if (x < 0) x += MOD;
    }
    Modular& operator += (Modular y){
        x += y.x;
        if (x >= MOD) x -= MOD;
        return *this;
    }
    Modular operator + (Modular y) {
        Modular tmp = *this;
        return tmp += y;
    }
 
    Modular& operator -= (Modular y){
        x -= y.x;
        if (x < 0) x += MOD;
        return *this;
    }
    Modular operator - (Modular y) {
        Modular tmp = *this;
        return tmp -= y;
    }
 
    Modular& operator *= (Modular y){
        x *= y.x;
        if (x >= MOD) x %= MOD;
        return *this;
    }
    Modular operator * (Modular y) {
        Modular tmp = *this;
        return tmp *= y;
    }
 
    // use at your own risk
    bool operator == (Modular y){
        return x == y.x;
    }
    bool operator != (Modular y){
        return x != y.x;
    }
};
ostream& operator << (ostream& out, Modular x){
    out << x.x;
    return out;
}

Modular fast_pow(Modular a, int n){
    Modular ans = 1;
    while(n > 0){
        if (n & 1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}
Modular inverse(Modular a){return fast_pow(a, MOD - 2);}

int k;
string inc(string s){
    reverse(ALL(s));
    int carry = 1;
    for(int i = 0; i < (int) s.size(); ++i){
        s[i] += carry;
        if (s[i] > '9'){
            s[i] -= 10;
            carry = 1;
        }
        else carry = 0;
    }
    if (carry) s.push_back('1');
    reverse(ALL(s));
    return s;
}

string dec(string s){
    reverse(ALL(s));
    int carry = 1;
    for(int i = 0; i < (int) s.size(); ++i){
        s[i] -= carry;
        if (s[i] < '0'){
            s[i] += 10;
            carry = 1;
        }
        else carry = 0;
    }
    while(s.back() == '0' && s.size() > 1) s.pop_back();
    reverse(ALL(s));
    return s;
}

namespace Sub1{
    const int N = 1069;
    Modular dp[N][18][6];
    bool visited[N][18][6];

    int nxt(int i, int j){
        if (i == 5 && j == 0) return i;
        return j % 5;
    }

    array<int, 3> gen_next(int x, int _j, int j){
        array<int, 3> ans; 
        fill(ALL(ans), -1);
        int idx = 0;
        if (x == 17) ans[idx++] = 17;
        else if (x <= 15){
            ans[idx++] = x ^ j;
            if ((x ^ j) == 0)
                ans[idx++] = 17;
        }
        else{
            ans[idx++] = 16;
            if (_j != 5){
                ans[idx++] = j;
                if (j == 0) 
                    ans[idx++] = 17;
            }
        }
        return ans;
    }

    Modular go_false(int digit, int x1, int last_num){
        if (digit == N) {
            return (x1 == 17);
        }
        if (visited[digit][x1][last_num]) return dp[digit][x1][last_num];
        visited[digit][x1][last_num] = true;
        Modular ans;
        for(int j = 0; j <= 9; ++j){
            if (last_num != 5 && (last_num + j) % 5 == 0) continue;
            int _j = nxt(last_num, j);
            array<int, 3> nxt1 = gen_next(x1, _j, j);
            for(int x: nxt1){
                if (x == -1) break;
                ans += go_false(digit + 1, x, _j);
            }
           
        }
        return dp[digit][x1][last_num] = ans;
    }

    void prepare(){
        for(int i = 0; i < N; ++i) for(int x1 = 0; x1 < 18; ++x1)
        for(int j = 0; j < 6; ++j) go_false(i, x1, j); 
    }
    
    ll mul[18];
    Modular go_true(string &s, int _digit, int digit, int last_num, array<int, 16> &cnt, int cur_xor){
        cnt[cur_xor]++;
        if (digit == N) {
            Modular sum = 0;
            for(int i: cnt) sum += i * (i-1) / 2;
            return sum;
        }
        int r = s[_digit] - '0';
        ll ans = 0;
        for(int j = 0; j <= r; ++j){
            if (last_num != 5 && (last_num + j) % 5 == 0) continue;
            int _j = nxt(last_num, j);
            if (j == r){
                ans += go_true(s, _digit + 1, digit + 1, _j, cnt, cur_xor ^ j).x;
                if (ans >= MOD * MOD) ans -= MOD * MOD;
            }
            else{
                if (_j == 5){
                    ans += go_false(digit + 1, 16, 5).x;
                    if (ans >= MOD * MOD) ans -= MOD * MOD;
                }
                else{
                    mul[16] = 1;
                    mul[17] = 0;
                    for(int i: cnt) mul[17] += i * (i-1) / 2;
                    mul[17] += cnt[cur_xor ^ j];
                    for(int i = 0; i < 16; ++i){
                        mul[i] = cnt[cur_xor ^ j ^ i];
                    }

                    if (digit + 1 < N){
                        for(int x = 0; x < 18; ++x){
                            ll cur = mul[x];
                            cur *= dp[digit + 1][x][_j].x;
                            ans += cur;
                            if (ans >= MOD * MOD) ans -= MOD * MOD;
                        }
                    }
                    else{
                        ans += mul[17];
                        if (ans >= MOD * MOD) ans -= MOD * MOD;
                    }
                }
            }
           
        }
        cnt[cur_xor]--;
        return ans % MOD;
    }

    Modular go(string s){
        if (s == "0") return 0;
        int n = s.size();
        array<int, 16> cnt;
        fill(ALL(cnt), 0);
        Modular ans = go_true(s, 0, N - n, 5, cnt, 0);

        return ans;
    }
}
namespace Sub2{
    const int N = 1069;
    Modular dp[N+1][18][18][6];

    int nxt(int i, int j){
        if (i == 5 && j == 0) return i;
        return j % 5;
    }

    array<int, 3> gen_next(int x, int _j, int j){
        array<int, 3> ans; 
        fill(ALL(ans), -1);
        int idx = 0;
        if (x == 17) ans[idx++] = 17;
        else if (x <= 15){
            ans[idx++] = x ^ j;
            if ((x ^ j) == 0)
                ans[idx++] = 17;
        }
        else{
            ans[idx++] = 16;
            if (_j != 5){
                ans[idx++] = j;
                if (j == 0) 
                    ans[idx++] = 17;
            }
        }
        return ans;
    }

    void prepare(){
        for(int j = 0; j < 6; ++j) dp[N][17][17][j] = 1;
        for(int digit = N-1; digit >= 0; --digit) for(int x1 = 0; x1 < 18; ++x1) for(int x2 = 0; x2 < 18; ++x2) 
        for(int last_num = 0; last_num < 6; ++last_num) {
            Modular ans;
            for(int j = 0; j <= 9; ++j){
                if (last_num != 5 && (last_num + j) % 5 == 0) continue;
                int _j = nxt(last_num, j);
                array<int, 3> nxt1 = gen_next(x1, _j, j), nxt2 = gen_next(x2, _j, j);
                for(int x: nxt1){
                    if (x == -1) break;
                    for(int y: nxt2){
                        if (y == -1) break;
                        ans += dp[digit + 1][x][y][_j];
                    }
                }
               
            }
            dp[digit][x1][x2][last_num] = ans;
        }
    }
    
    ll mul[18];

    Modular go_true(string &s, int _digit, int digit, int last_num, array<int, 16> &cnt, int cur_xor){
        cnt[cur_xor]++;
        if (digit == N) {
            Modular sum = 0;
            for(int i: cnt) sum += i * (i-1) / 2;
            return sum * sum;
        }
        int r = s[_digit] - '0';
        ll ans = 0;
        
        for(int j = 0; j <= r; ++j){
            if (last_num != 5 && (last_num + j) % 5 == 0) continue;
            int _j = nxt(last_num, j);
            if (j == r){
                ans += go_true(s, _digit + 1, digit + 1, _j, cnt, cur_xor ^ j).x;
                if (ans >= MOD * MOD) ans -= MOD * MOD;
            }
            else{
                if (_j == 5){
                    ans += dp[digit + 1][16][16][5].x;
                    if (ans >= MOD * MOD) ans -= MOD * MOD;
                }
                else{
                    mul[16] = 1;
                    mul[17] = 0;
                    for(int i: cnt) mul[17] += i * (i-1) / 2;
                    mul[17] += cnt[cur_xor ^ j];
                    for(int i = 0; i < 16; ++i){
                        mul[i] = cnt[cur_xor ^ j ^ i];
                    }

                    for(int x = 0; x < 18; ++x) if (mul[x]) for(int y = 0; y < 18; ++y) if (mul[y]){
                        ll cur = mul[x] * mul[y];
                        if (cur >= MOD) cur %= MOD;
                        cur *= dp[digit + 1][x][y][_j].x;
                        ans += cur;
                        if (ans >= MOD * MOD) ans -= MOD * MOD;
                    }
                }
            }
           
        }
        cnt[cur_xor]--;
        return ans % MOD;
    }

    Modular go(string s){
        if (s == "0") return 0;
        int n = s.size();
        array<int, 16> cnt;
        fill(ALL(cnt), 0);
        Modular ans = go_true(s, 0, N - n, 5, cnt, 0);

        return ans;
    }
}

void solve(){
    string l, r; cin >> l >> r;
    l = dec(l);

    Modular ans;
    if (k == 1) ans = Sub1::go(r) - Sub1::go(l);
    else ans = Sub2::go(r) - Sub2::go(l);

    cout << ans << "\n";
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    freopen("PNUM.INP", "r", stdin);
    freopen("PNUM.OUT", "w", stdout);

    clock_t start = clock();

    Sub1::prepare();
    Sub2::prepare();

    cin >> k;
    int t; cin >> t;
    while(t--) solve();

    cerr << "Time elapsed: " << clock() - start << " ms\n";
    return 0;
}
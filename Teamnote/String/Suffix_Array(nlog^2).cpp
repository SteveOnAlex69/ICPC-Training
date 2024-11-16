
/* I HAVE NO THING TO SAY. IT REALLY O(nlog2). */


const int LOG_N = 17, N = 1e5 + 69; // modify this
 
int spare_table[LOG_N][N];
vector<int> gen_sa(string s){
    int n = s.size();
    vector<int> perm(n);
    for(int i = 0; i<n; ++i) perm[i] = i;
 
    vector<int> bruh(n);
    for(int i = 0; i<n; ++i) bruh[i] = spare_table[0][i] = s[i] - 'a' + 1;
 
    for(int j = 1; j < LOG_N; ++j){
        vector<ll> cost(n);
        for(int i = 0; i<n; ++i){
            int _i = (i + MASK(j-1)) % n;
            cost[i] = 1LL * bruh[i] * N + bruh[_i];
        }
        if (j == 1)sort(ALL(perm), [&cost](int x, int y){return cost[x] < cost[y];});
        else{
            int last = 0;
            for(int i = 0; i<perm.size(); ++i){
                if (i + 1 == perm.size() || bruh[perm[i]] != bruh[perm[i+1]]){
                    sort(perm.begin() + last, perm.begin() + i + 1, [&cost](int x, int y){return cost[x] < cost[y];});
                    last = i + 1;
                }
            }
        }
 
        int cnt = 0;
        for(int i = 0; i<n; ++i){
            if (i >= 1){
                int x = perm[i-1], y = perm[i];
                if (cost[x] != cost[y]) cnt++;
            }
            bruh[perm[i]] = spare_table[j][perm[i]] = cnt;
        }
    }
    return perm;
}
int lcp(int u,int v){
    int ans = 0;
    for(int j = LOG_N - 1; j>=0; --j) if (spare_table[j][u] == spare_table[j][v]){
        ans += MASK(j);
        u += MASK(j); v += MASK(j);
        if (u > n) u -= n+1; 
        if (v > n) v -= n+1;
    }
    return ans;
}
 
 
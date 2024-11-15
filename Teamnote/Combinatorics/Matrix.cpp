/*
Usage:
- Good old matrix
*/


struct Matrix{
    int n, m; 
    vector<vector<Modular>> a;

    Matrix(int n, int m): n(n), m(m){
        a.resize(n, vector<Modular>(m));
    }

    Matrix operator * (Matrix b){
        if (m != b.n) assert(1);
        Matrix res(n, b.m);
        for(int i = 0; i<n; ++i) 
        for(int j = 0; j<b.m; ++j)
        for(int k = 0; k<m; ++k)
            res.a[i][j] += a[i][k] * b.a[k][j];
        return res;
    }
};

Matrix fast_pow(Matrix a, ll n){
    if (n == 1) return a;
    Matrix t = fast_pow(a, n / 2);
    if (n % 2 == 0) return t * t;
    return t * t * a;
}

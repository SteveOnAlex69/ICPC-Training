
/* THIS IS POLLARD RHO AND I HAVE NO IDEA WHAT ITS USAGE IS */
\

unsigned long long mod_mul(unsigned long long a, unsigned long long b, unsigned long long mod) {
    unsigned long long res = 0;
    a %= mod;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (2 * a) % mod;
        b >>= 1;
    }
    return res;
}

unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long res = 1;
    base %= mod;
    while (exp) {
        if (exp & 1) res = mod_mul(res, base, mod);
        base = mod_mul(base, base, mod);
        exp >>= 1;
    }
    return res;
}

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    return b ? gcd(b, a % b) : a;
}

bool miller_rabin(unsigned long long n, int iterations = 5) {
    if (n < 4) return n == 2 || n == 3;
    unsigned long long d = n - 1;
    while (d % 2 == 0) d /= 2;
    for (int i = 0; i < iterations; ++i) {
        unsigned long long a = 2 + rand() % (n - 4);
        unsigned long long x = mod_exp(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool is_composite = true;
        for (unsigned long long temp = d; temp != n - 1; temp *= 2) {
            x = mod_mul(x, x, n);
            if (x == n - 1) {
                is_composite = false;
                break;
            }
        }
        if (is_composite) return false;
    }
    return true;
}

unsigned long long pollards_rho(unsigned long long n) {
    if (n % 2 == 0) return 2;
    unsigned long long x = 2, y = 2, d = 1, c = rand() % (n - 1) + 1;
    while (d == 1) {
        x = (mod_mul(x, x, n) + c) % n;
        y = (mod_mul(mod_mul(y, y, n) + c, y, n) + c) % n;
        d = gcd(x > y ? x - y : y - x, n);
    }
    return (d == n) ? pollards_rho(n) : d;
}

void factorize(unsigned long long n, std::vector<unsigned long long> &factors) {
    if (n == 1) return;
    if (miller_rabin(n)) {
        factors.push_back(n);
        return;
    }
    unsigned long long factor = pollards_rho(n);
    factorize(factor, factors);
    factorize(n / factor, factors);
}

std::vector<unsigned long long> get_prime_factors(unsigned long long n) {
    std::vector<unsigned long long> factors;
    factorize(n, factors);
    std::sort(factors.begin(), factors.end());
    return factors;
}
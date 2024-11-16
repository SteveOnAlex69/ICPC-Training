
/* THIS IS POLLARD RHO AND I HAVE NO IDEA WHAT ITS USAGE IS */

// GCD function
long long gcd(long long a, long long b) {
    while (b) a %= b, swap(a, b);
    return a;
}

// Pollard's Rho
long long pollardsRho(long long n) {
    long long x = rand() % (n - 1) + 1, y = x, c = rand() % (n - 1) + 1, d = 1;
    while (d == 1) {
        x = (x * x + c) % n;
        y = (y * y + c) % n;
        y = (y * y + c) % n;
        d = gcd(abs(x - y), n);
        if (d > 1) return d;
    }
    return d;
}
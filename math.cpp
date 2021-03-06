
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return a * b * gcd(a, b); }

// 素因数
vector<int> getPrimeFactors(int a) {
    vector<int> s;
    for (int i = 2; i * i <= a; i++) {
        if (a % i != 0) continue;
        while (a % i == 0) {
            s.push_back(i);
            a /= i;
        }
    }
    if (a > 1) s.push_back(a);
    return s;
}

// 素因数
set<int> getPrimeFactors(int a) {
    set<int> s;
    for (int i = 2; i * i <= a; i++) {
        if (a % i != 0) continue;
        s.insert(i);
        while (a % i == 0) a /= i;
    }
    if (a > 1) s.insert(a);
    return s;
}

vector<int> getPrimeFactors(int a) {
    vector<int> s;
    for (int i = 2; i * i <= a; i++) {
        if (a % i != 0) continue;
        s.push_back(i);
        while (a % i == 0) a /= i;
    }
    if (a > 1) s.push_back(a);
    return s;
}


// mod
int mod = 1e9 + 7;

void add(int& a, int b) {
    a += b;
    if (a >= mod) a-= mod;
}
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }

template<class... T>
int add(int x, T... y) { return add(x, add(y...)); }

int mul(int x, int y) { return 1LL * x * y % mod; }

template<class... T>
int mul(int x, T... y) { return mul(x, mul(y...)); }

int sub(int x, int y) { return add(x, mod - y); }

// nCr
int fac[200005], rev[200005];

int binpow(int x, int p) {
    if (p == 0) return 1;

    if (p % 2 == 0)
        return binpow((x * x) % mod, p / 2);
    else
        return (x * binpow(x, p - 1)) % mod;
}

int nCr(int n, int r) {
    if (r > n) return 0;
    return ((fac[n] * rev[r]) % mod * rev[n - r]) % mod;
}

void precalc(int n) {
    fac[0] = fac[1] = 1;
    FOR(i, 2, n + 2)
    fac[i] = (fac[i - 1] * i) % mod;

    rev[n + 1] = binpow(fac[n + 1], mod - 2) % mod;
    REV(i, n, 0)
    { rev[i] = (rev[i + 1] * (i + 1)) % mod; }
}

// 逆元
int modinv(int a, int m) {
    int b = m, u = 1, v = 0;
    while (b) {
        int t = a / b;
        a -= t * b;
        swap(a, b);
        u -= t * v;
        swap(u, v);
    }
    u %= m;
    if (u < 0) u += m;
    return u;
}


//　行列累乗

typedef vector<int> Vec;
typedef vector<Vec> Mat;

Vec mulMatVec(Mat a, Vec b) {
    int n = b.size();
    Vec ret(n, 0);
    REP(i, n)REP(j, n)ret[i] = add(ret[i], mul(a[i][j], b[j]));
    return ret;
}

Mat mulMatMat(Mat a, Mat b) {
    int n = a.size();
    Mat ret(n, Vec(n, 0));
    REP(i, n)REP(j, n)REP(k, n)ret[i][j] = add(ret[i][j], mul(a[i][k], b[k][j]));
    return ret;
}

Mat fastPow(Mat x, int n) {
    Mat ret(x.size(), Vec(x.size(), 0));
    REP(i, x.size())ret[i][i] = 1;
    while (0 < n) {
        if ((n % 2) == 0) {
            x = mulMatMat(x, x);
            n >>= 1;
        } else {
            ret = mulMatMat(ret, x);
            --n;
        }
    }
    return ret;
}

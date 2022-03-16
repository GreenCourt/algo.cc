struct modint {
  //static const int MOD = 998244353; // Are they coprime?
  static const int MOD = 1000000007; // Are they coprime?
  long long val;
  modint(long long val=0) : val((val % MOD + MOD) % MOD){}
  modint operator-() const { return modint(-val); }
  modint& operator+=(const modint a) { if ((val += a.val)     >= MOD) val -= MOD; return *this; }
  modint& operator-=(const modint a) { if ((val += MOD-a.val) >= MOD) val -= MOD; return *this; }
  modint& operator*=(const modint a) { (val *= a.val) %= MOD; return *this; }
  modint operator+(const modint a) const { return (modint)*this += a; }
  modint operator-(const modint a) const { return (modint)*this -= a; }
  modint operator*(const modint a) const { return (modint)*this *= a; }
  modint pow(long long n) const { modint r(1), m(val); while (n > 0) { if (n & 1) {r *= m;} m *= m; n >>= 1; } return r; }
  modint inv() const {
    //assert(gcd(val,MOD)==1);
    long long a = val, b = MOD, u = 1, v = 0;
    while (b) { long long t = a / b; a -= t * b; swap(a, b); u -= t * v; swap(u, v); }
    return (modint)u;
  }
  modint& operator/=(const modint a) { return (*this) *= a.inv(); }
  modint operator/(const modint a) const { return (modint)*this /= a; }
  bool operator==(const modint &p) const { return val == p.val; }
  bool operator!=(const modint &p) const { return val != p.val; }
  friend ostream &operator<<(ostream &os, const modint &p) { return os << p.val; }
  friend istream &operator>>(istream &is, modint &a) { long long t; is >> t; a = modint(t); return (is); }
  static modint choose(int n, int k) {
    /* O(k log MOD) */
    assert(n>=0 && k>=0 && n < MOD && k < MOD);
    modint c = 1;
    for(int i=1; i<=k; i++) c *= modint(n-i+1) / i;
    return c;
  }
  static modint permutation(long long n, int k) {
    /* O(k) */
    assert(n>=0 && k>=0);
    modint c = 1;
    for(long long i=n; i>n-k; --i) c *= modint(i);
    return c;
  }
};

struct ModBinomial {
  vector<modint> fact, fact_inv, inv;
  ModBinomial(int n) : fact(n+1, 1), fact_inv(n+1, 1), inv(n+1, 1) {
    /* O(n) */
    assert(n < modint::MOD);
    for (int i = 2; i <= n; i++) {
      fact[i] = fact[i - 1] * i;
      inv[i] = -inv[modint::MOD % i] * (modint::MOD / i);
      fact_inv[i] = fact_inv[i - 1] * inv[i];
    }
  }
#if 1
  modint choose(int n, int k) { /* O(1) */ assert(n>=0 && k>=0); return n < k ? 0 : fact[n] * fact_inv[k] * fact_inv[n - k]; }
#else
  modint choose(int n, int k) {
    /* O(k) */
    assert(n>=0 && k>=0 && n < modint::MOD && k < modint::MOD);
    modint c = 1;
    for(int i=1; i<=k; i++) c *= modint(n-i+1);
    return c * fact_inv[k];
  }
#endif
  modint permutation(int n, int k) { /* O(1) */ assert(n>=0 && k>=0); return n < k ? 0 : fact[n] * fact_inv[n - k]; }
};

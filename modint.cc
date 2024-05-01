template <int MOD>
struct Modint {
  long long val;
  Modint(long long val_ = 0) : val((val_ % MOD + MOD) % MOD){}
  Modint operator-() const { return Modint(-val); }
  Modint& operator+=(const Modint a) { if ((val += a.val)     >= MOD) val -= MOD; return *this; }
  Modint& operator-=(const Modint a) { if ((val += MOD-a.val) >= MOD) val -= MOD; return *this; }
  Modint& operator*=(const Modint a) { (val *= a.val) %= MOD; return *this; }
  Modint operator+(const Modint a) const { return (Modint)*this += a; }
  Modint operator-(const Modint a) const { return (Modint)*this -= a; }
  Modint operator*(const Modint a) const { return (Modint)*this *= a; }
  Modint pow(long long n) const { Modint r(1), m(val); while (n > 0) { if (n & 1) {r *= m;} m *= m; n >>= 1; } return r; }
  Modint inv() const {
#ifdef _GLIBCXX_ASSERTIONS
    assert(gcd(val,MOD)==1);
#endif
    long long a = val, b = MOD, u = 1, v = 0;
    while (b) { long long t = a / b; a -= t * b; swap(a, b); u -= t * v; swap(u, v); }
    return (Modint)u;
  }
  Modint& operator/=(const Modint a) { return (*this) *= a.inv(); }
  Modint operator/(const Modint a) const { return (Modint)*this /= a; }
  bool operator==(const Modint &p) const { return val == p.val; }
  bool operator!=(const Modint &p) const { return val != p.val; }
  template <typename T> friend Modint operator+(T t, const Modint& a) { static_assert(is_integral<T>::value, "not an integral type"); return a + t; }
  template <typename T> friend Modint operator-(T t, const Modint& a) { static_assert(is_integral<T>::value, "not an integral type"); return -a + t; }
  template <typename T> friend Modint operator*(T t, const Modint& a) { static_assert(is_integral<T>::value, "not an integral type"); return a * t; }
  template <typename T> friend Modint operator/(T t, const Modint& a) { static_assert(is_integral<T>::value, "not an integral type"); return a.inv() * t; }
  friend ostream &operator<<(ostream &os, const Modint &p) { return os << p.val; }
  friend istream &operator>>(istream &is, Modint &a) { long long t; is >> t; a = Modint(t); return (is); }
  static int mod() { return MOD; }
  static Modint choose(long long n, int k) {
    /* O(k log MOD) */
    assert(n>=0 && k>=0 && k < MOD);
    Modint c = 1;
    for(int i=1; i<=k; i++) c *= Modint(n-i+1) / i;
    return c;
  }
  static Modint permutation(long long n, int k) {
    /* O(k) */
    assert(n>=0 && k>=0);
    Modint c = 1;
    for(long long i=n; i>n-k; --i) c *= Modint(i);
    return c;
  }
};
using modint = Modint<998244353>;
//using modint = Modint<1000000007>;

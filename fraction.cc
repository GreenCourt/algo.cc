struct Frac {
  long long numerator, denominator;
  constexpr static bool normalized = true;
  Frac(long long numerator_ = 0, long long denominator_ = 1) : numerator(numerator_), denominator(denominator_) {
    assert(denominator != 0);
    if(denominator < 0) numerator *= -1, denominator *= -1;
    if(numerator == 0) denominator = 1;
    if(normalized) normalize();
  }
  inline void normalize() { /* O(log n) */
    if(denominator < 0) numerator *= -1, denominator *= -1;
    if(numerator == 0) denominator = 1;
    long long g = gcd(numerator, denominator);
    numerator /= g, denominator /= g;
  }
  Frac operator-() const { return Frac(-numerator, denominator); }
  Frac& operator+=(const Frac a) {
    long long g = normalized ? gcd(denominator, a.denominator) : 1;
    numerator = a.denominator/g * numerator + denominator/g * a.numerator;
    denominator = denominator / g * a.denominator;
    if(normalized) normalize();
    return *this;
  }
  Frac& operator-=(const Frac a) { return (*this) += -a; }
  Frac& operator*=(const Frac a) {
    long long g1 = normalized ? gcd(numerator, a.denominator) : 1;
    long long g2 = normalized ? gcd(a.numerator, denominator) : 1;
    numerator = (numerator/g1) * (a.numerator/g2), denominator = (denominator/g2) * (a.denominator/g1);
    return *this;
  }
  Frac inv() const { assert(numerator != 0); return (numerator < 0) ? Frac(-denominator, -numerator) : Frac(denominator, numerator); }
  Frac& operator/=(const Frac a) { return (*this) *= a.inv(); }
  Frac operator+(const Frac a) const { return (Frac)*this += a; }
  Frac operator-(const Frac a) const { return (Frac)*this -= a; }
  Frac operator*(const Frac a) const { return (Frac)*this *= a; }
  Frac operator/(const Frac a) const { return (Frac)*this /= a; }
  bool operator<(const Frac &f) const { return numerator*f.denominator < f.numerator*denominator; }
  bool operator<=(const Frac &f) const { return numerator*f.denominator <= f.numerator*denominator; }
  bool operator>(const Frac &f) const { return numerator*f.denominator > f.numerator*denominator; }
  bool operator>=(const Frac &f) const { return numerator*f.denominator >= f.numerator*denominator; }
  bool operator==(const Frac &f) const { return numerator*f.denominator == f.numerator*denominator; }
  bool operator!=(const Frac &f) const { return numerator*f.denominator != f.numerator*denominator; }
  friend ostream &operator<<(ostream &os, const Frac &p) { return os << p.numerator << '/' << p.denominator; }
};

struct FracVector {
  long long x, y;
  FracVector(long long x_ = 0, long long y_ = 0): x(x_), y(y_){}

  inline bool arg_lt(const FracVector &f) const { return y*f.x < f.y*x; }
  inline bool arg_gt(const FracVector &f) const { return y*f.x > f.y*x; }
  inline bool arg_eq(const FracVector &f) const { return y*f.x == f.y*x; }

  inline bool coordinate_lt(const FracVector& a) const { return x!=a.x ? x < a.x : y < a.y; }
  inline bool coordinate_gt(const FracVector& a) const { return x!=a.x ? x > a.x : y > a.y; }
  inline bool coordinate_eq(const FracVector& a) const { return x==a.x && y==a.y; }

#if 0 // compare by coordinates
  bool operator<(const FracVector& a) const { return coordinate_lt(a); }
  bool operator>(const FracVector& a) const { return coordinate_gt(a); }
  bool operator<=(const FracVector& a) const { return coordinate_lt(a) || coordinate_eq(a);}
  bool operator>=(const FracVector& a) const { return coordinate_gt(a) || coordinate_eq(a);}
  bool operator==(const FracVector& a) const { return coordinate_eq(a); }
#else // compare by arguments
  bool operator<(const FracVector& a) const { return arg_lt(a);}
  bool operator>(const FracVector& a) const { return arg_gt(a);}
  bool operator<=(const FracVector& a) const { return arg_lt(a) || arg_eq(a);}
  bool operator>=(const FracVector& a) const { return arg_gt(a) || arg_eq(a);}
  bool operator==(const FracVector& a) const { return arg_eq(a);}
#endif

  friend istream &operator>>(istream& is, FracVector& p) {long long x_,y_; is >> x_ >> y_; p = FracVector(x_,y_); return is; }
  friend ostream &operator<<(ostream& os, const FracVector& p) {os<<"("<<p.x<<","<<p.y<<")"; return os;}
};

struct FracLine {
  long long a, b, c; /* ax + by = c */
  FracLine(long long x1, long long y1, long long x2, long long y2) {
    assert(x1 != x2 || y1 != y2);
    if(x1 == x2) { a = 1, b = 0, c = x1; return; }
    if(y1 == y2) { a = 0, b = 1, c = y1; return; }

    Frac A(y1-y2, x1-x2); // y = Ax + C
    Frac C = Frac(y1) - A*x1;
    b = lcm(A.denominator, C.denominator);
    a = (A*b).numerator;
    c = (C*b).numerator;
  }
  tuple<long long,long long,long long> to_tuple() const { return make_tuple(a,b,c); }
};

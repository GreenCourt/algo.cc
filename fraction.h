struct Frac{
  long long numerator, denominator;
  Frac(long long numerator=0, long long denominator=1, bool normalized=false) : numerator(numerator), denominator(denominator) {
    /* O(log n) if normalized else O(1) */
    if(normalized) normalize();
  }
  void normalize() {
    /* O(log n) */
    long long g = gcd(numerator, denominator);
    numerator /= g, denominator /= g;
  }
  bool operator<(const Frac &f) const { return numerator*f.denominator < f.numerator*denominator; }
  bool operator<=(const Frac &f) const { return numerator*f.denominator <= f.numerator*denominator; }
  bool operator>(const Frac &f) const { return numerator*f.denominator > f.numerator*denominator; }
  bool operator>=(const Frac &f) const { return numerator*f.denominator >= f.numerator*denominator; }
  bool operator==(const Frac &f) const { return numerator*f.denominator == f.numerator*denominator; }
  bool operator!=(const Frac &f) const { return numerator*f.denominator != f.numerator*denominator; }
  friend ostream &operator<<(ostream &os, const Frac &p) { return os << p.numerator << '/' << p.denominator; }
};

long long saturating_mul(long long a, long long b, long long limit=(long long)1e18+1) {
  /* O(1) */
  assert(limit>=0);
  long long sign = ((a<0) != (b<0)) ? -1 : 1;
  return ((b!=0) && (abs(a) > limit / abs(b))) ? limit * sign : a*b;
}

long long saturating_pow(long long a, int n, long long limit=(long long)1e18+1) {
  /* O(log n) */
  assert(n>=0 && limit>=0);
  long long r = 1;
  while (n > 0) {
    if (n & 1) r = saturating_mul(r, a, limit);
    a = saturating_mul(a, a, limit);
    n >>= 1;
  }
  return r;
}

long long isqrt(long long x) {
  /* O(log x) */
  /* return ceil(sqrt(x)) for an integer */
  if(x==0) return 0;
  long long sgn = x >= 0 ? 1 : -1;
  x = abs(x);
  auto f = [&](long long a) { return (a==0 || a <= x/a) && a*a<=x; };
  long long l = 0, r=x;
  bool fl = f(l), fr = f(r); assert(fl!=fr);
  long long &T = fl ? l : r, &F = fr ? l : r;
  while(r-l>1) {
    long long m = l + (r-l) / 2;
    if(f(m)) T = m;
    else F = m;
  }
  return T * sgn;
}

long long iceil(long long x, long long base) {
  /* O(1) */
  // return minimum y that satisfies (x<=y) and (y%base == 0)
  bool negative = x < 0;
  x = abs(x);
  if(negative) return -(x - (x % base));
  else return x + ((x % base) ? base - (x % base) : 0);
}

long long ifloor(long long x, long long base) {
  /* O(1) */
  // return maximum y that satisfies (x>=y) and (y%base == 0)
  bool negative = x < 0;
  x = abs(x);
  if(negative) return -(x + ((x % base) ? base - (x % base) : 0)) ;
  else return x - (x % base);
}

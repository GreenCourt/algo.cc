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

int modpow(long long a, long long n, int mod) {
  /* O(log n) */
  assert(a>=0 && n >= 0);
  a %= mod;
  long long r = 1;
  while (n > 0) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return (int)r;
}

int modinv(long long a, int mod) {
  /* O(log mod) */
  assert(a>=0);
  assert(gcd(a,mod)==1);
  long long b = mod, u = 1, v = 0;
  while (b) {
    long long t = a / b;
    a -= t * b; swap(a, b);
    u -= t * v; swap(u, v);
  }
  u %= mod;
  if (u < 0) u += mod;
  return (int)u;
}

int choose(int n, int k, int mod) {
  /* O(k log mod) */
  assert(n>=0 && k>=0 && n < mod && k < mod);
  long long c = 1;
  for(int i=1; i<=k; i++) c = (n-i+1) % mod * c % mod * modinv(i, mod) % mod; 
  return (int)c;
}

int permutation(long long n, int k, int mod) {
  /* O(k) */
  assert(n>=0 && k>=0);
  long long c = 1;
  for(long long i=n; i>n-k; --i) c = i % mod * c % mod;
  return (int)c;
}

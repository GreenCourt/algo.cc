template<typename T>
struct RollingHash {
  const T& text;
  int n;
  long long mod;
  vector<long long> pow_b, hash;
  // hash( [0,r) ) = sum([text[i] * pow(b, n-i-1) for i in range(n)])
  // hash( [l,r) ) = hash( [0,r) ) - pow(b, r - l) * hash( [0,l) )

  RollingHash(const T& text, long long b = 100000007, long long mod = 1000000007) : text(text), n(text.size()), mod(mod) {
      /* O(n) */
      assert(n > 0);
      pow_b = vector<long long>(n+1, 1LL);
      hash.resize(n+1);

      pow_b[0] = 1, hash[0] = 0;
      for(int i=1; i<=n; ++i) {
        pow_b[i] = pow_b[i-1] * b % mod;
        hash[i] = ((b * hash[i-1] % mod) + text[i-1]) % mod;
      }
    }
  long long get(int l, int r) { // [l,r)
    /* O(1) */
    assert(0 <= l && l <= r && r <= n);
    long long x = hash[r] - pow_b[r-l] * hash[l] % mod; 
    if(x < 0) x += mod;
    return x;
  }
  long long get(int r) { // [0,r)
    /* O(1) */
    assert(0 <= r && r <= n);
    return hash[r];
  }
};

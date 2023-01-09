template<typename T>
struct RollingHash {
  const T& text;
  int n;
  vector<unsigned long long> pow_b;
  vector<unsigned long long> hash;
  // hash( [0,r) ) = sum([text[i] * pow(b, n-i-1) for i in range(n)])
  // hash( [l,r) ) = hash( [0,r) ) - pow(b, r - l) * hash( [0,l) )

  RollingHash(const T& text, unsigned long long b=1000000007) : text(text), n(text.size()) {
    /* O(n) */
    assert(n > 0);
    pow_b = vector<unsigned long long>(n+1, 1ULL);
    hash.resize(n+1);

    /* For unsigned long long, overflow is same as mod 2^64 */
    pow_b[0] = 1, hash[0] = 0;
    for(int i=1; i<=n; ++i) {
      pow_b[i] = pow_b[i-1] * b;
      hash[i] = b * hash[i-1] + text[i-1];
    }
  }
  unsigned long long get(int l, int r) { // [l,r)
    /* O(1) */
    assert(0 <= l && l <= r && r <= n);
    return hash[r] - pow_b[r-l] * hash[l]; 
  }
  unsigned long long get(int r) { // [0,r)
    /* O(1) */
    assert(0 <= r && r <= n);
    return hash[r];
  }
};

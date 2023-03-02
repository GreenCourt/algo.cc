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
  modint choose(long long n, int k) {
    /* O(k) for n of long long */
    assert(n>=0 && k>=0 && k < modint::MOD);
    modint c = 1;
    for(int i=1; i<=k; i++) c *= modint(n-i+1);
    return c * fact_inv[k];
  }
#endif
  modint permutation(int n, int k) { /* O(1) */ assert(n>=0 && k>=0); return n < k ? 0 : fact[n] * fact_inv[n - k]; }
};

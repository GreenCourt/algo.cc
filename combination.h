struct combination {
  /* initialize: O(n) */
  /* choose    : O(1) */
  vector<long long> fact;
  combination(int n=1) : fact(n+1) {
    fact[0] = 1, fact[1] = 1;
    for (int i = 2; i <= n; i++) fact[i] = fact[i - 1] * i;
  }
  long long choose(int n, int k) { return fact[n] / fact[k] / fact[n - k]; }
};

long long choose(int n, int k) {
    /* O(k) */
    long long ret = 1;
    for(long long i = 1; i <= k; ++i) ret = (ret * n--) / i;
    return ret;
}
struct combination {
  /* initialize: O(n^2) */
  /* choose    : O(1) */
  vector<vector<long long>> c;
  combination(int n=1) : c(n+1, vector<long long>(n+1)) {
    c[0][0] = 1;
    for(int i=0; i<n; ++i) for(int j=0; j<=i; ++j)
      c[i+1][j] += c[i][j], c[i+1][j+1] += c[i][j];
  }
  long long choose(int n, int k) {
    assert(n>=0 && n<ssize(c) && k>=0);
    return c[n][k];
  }
};

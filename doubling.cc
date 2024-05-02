struct Doubling {
  vector<vector<int>> dbl;
  Doubling(const vector<int> &single_move, long long k) { /* O(n log k) */
    int n = ssize(single_move), log2k = log2floor(k);
    dbl.assign(log2k+1, vector<int>(n));
    dbl[0] = vector(single_move);
    for(int i=0; i<log2k; ++i) for(int x=0; x<n; ++x) dbl[i+1][x] = dbl[i][dbl[i][x]];
  }
  static int log2floor(unsigned long long k) { /* O(log k) */
    int log2k = 0; for(unsigned long long K=k; K>1; K/=2) log2k++;
    return log2k; // floor(log2(k)) if k>0 else 0
  }
  int query(int start, long long k) { /* O(log k) */
    assert(k < (1LL<<dbl.size()));
    int x = start;
    while(k) {
      int lk = log2floor(k);
      x = dbl[lk][x], k -= 1LL<<lk;
    }
    return x;
  }
};

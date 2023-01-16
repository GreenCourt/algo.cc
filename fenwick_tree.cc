struct fenwick_tree {
  int n;
  vector<long long> node;
  fenwick_tree(int n=0) : n(n), node(n) {}
  void add(int i, long long x) {
    ++i;
    while(i<=n) {
      node[i-1] += x;
      i += i & -i;
    }
  }
  long long sum(int r) { /* [0, r) */
    assert(r>=0);
    long long s = 0;
    while(r) {
      s += node[r-1];
      r -= r & -r;
    }
    return s;
  }
  long long sum(int l, int r) { /* [l, r) */
    assert(0<=l && l<=r && r<=n);
    return sum(r) - sum(l);
  }
};

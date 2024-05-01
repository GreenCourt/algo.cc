template<typename T=long long>
struct fenwick_tree {
  int n;
  vector<T> node;
  fenwick_tree(int n_ = 0) : n(n_), node(n_) {}
  void add(int i, T x) {
    ++i;
    while(i<=n) {
      node[i-1] += x;
      i += i & -i;
    }
  }
  T sum(int r) { /* [0, r) */
    assert(r>=0);
    T s = 0;
    while(r) {
      s += node[r-1];
      r -= r & -r;
    }
    return s;
  }
  T sum(int l, int r) { /* [l, r) */
    assert(0<=l && l<=r && r<=n);
    return sum(r) - sum(l);
  }
};

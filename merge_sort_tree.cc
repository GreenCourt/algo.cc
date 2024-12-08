template <class S> struct merge_sort_tree {
  merge_sort_tree(const vector<S>& data) : n(ssize(data)) {
    /* O(n log n) */
    int msb = 1; while((msb<<1) <= n) msb <<= 1;
    leafs = (n==msb) ? n : msb << 1;
    node = vector<vector<S>>(2 * leafs);
    for(int i=0; i<n; i++) node[i+leafs] = vector{data[i]};
    for(int i=leafs-1; i>0; --i) merge(node[i], node[l_child(i)], node[r_child(i)]);
  }

  int count(int l, int r, S low, S high) { // [l, r), [low, high)
    /* O(n log^2 n) */
    /* count data[i] s.t low <= data[i] < high && l <= i < r */
    assert(0 <= l && l <= r && r <= n);
    assert(low <= high);
    auto f = [&] (const vector<S> &nd) {
      return lower_bound(nd.begin(), nd.end(), high) - lower_bound(nd.begin(), nd.end(), low);
    };
    int cnt = 0;
    l += leafs, r += leafs;
    while(l < r) {
      if(l & 1) cnt += f(node[l++]);
      if(r & 1) cnt += f(node[--r]);
      l = parent(l), r = parent(r);
    }
    return cnt;
  }

  private:
  int n, leafs;
  vector<vector<S>> node;
  static inline int r_child(int v) { return v*2+1; }
  static inline int l_child(int v) { return v*2; }
  static inline int parent(int v) { return v/2; }

  static void merge(vector<S> &p, const vector<S> &l, const vector<S> &r) {
    /* O(|l| + |r|) */
    assert(p.empty());
    p.reserve(l.size() + r.size());
    int lsz = ssize(l), rsz = ssize(r);
    int li = 0, ri = 0;
    while(li < lsz && ri < rsz) {
      if(l[li] < r[ri]) p.push_back(l[li++]);
      else p.push_back(r[ri++]);
    }
    while(li < lsz) p.push_back(l[li++]);
    while(ri < rsz) p.push_back(r[ri++]);
  }
};

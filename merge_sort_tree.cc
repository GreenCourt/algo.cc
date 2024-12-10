template <class S> struct merge_sort_tree {
  merge_sort_tree(const vector<S>& data) : n(ssize(data)) {
    /* O(n log n) */
    int msb = 1; while((msb<<1) <= n) msb <<= 1;
    leafs = (n==msb) ? n : msb << 1;
    node = vector<vector<S>>(2 * leafs);
    for(int i=0; i<n; i++) node[i+leafs] = vector{data[i]};
    for(int i=leafs-1; i>0; --i) node[i] = merge(node[l_child(i)], node[r_child(i)]);
  }

  int count(int l, int r, S low, S high) { // [l, r), [low, high)
    /* O(log^2 n) */
    /* count number of data[i] s.t low <= data[i] < high && l <= i < r */
    assert(0 <= l && l <= r && r <= n);
    assert(low <= high);
    int cnt = 0;
    for(int i : extract_nodes(l, r)) {
      vector<S> &nd = node[i];
      cnt += lower_bound(nd.begin(), nd.end(), high) - lower_bound(nd.begin(), nd.end(), low);
    }
    return cnt;
  }

  protected:
  int n, leafs;
  vector<vector<S>> node;
  static inline int r_child(int v) { return v*2+1; }
  static inline int l_child(int v) { return v*2; }
  static inline int parent(int v) { return v/2; }

  vector<int> extract_nodes(int l, int r) {
    /* O(log n) */
    /* return node indices s.t the union of their elements covers [l,r) exactly */
    assert(0 <= l && l <= r && r <= n);
    vector<int> indices;
    auto push = [&](int i) { if(!node[i].empty()) indices.push_back(i); };
    l += leafs, r += leafs;
    while(l < r) {
      if(l & 1) push(l++);
      if(r & 1) push(--r);
      l = parent(l), r = parent(r);
    }
    return indices;
  }

  static vector<S> merge(const vector<S> &l, const vector<S> &r) {
    /* O(|l| + |r|) */
    vector<S> p;
    p.reserve(l.size() + r.size());
    int lsz = ssize(l), rsz = ssize(r);
    int li = 0, ri = 0;
    while(li < lsz && ri < rsz) {
      if(l[li] < r[ri]) p.push_back(l[li++]);
      else p.push_back(r[ri++]);
    }
    while(li < lsz) p.push_back(l[li++]);
    while(ri < rsz) p.push_back(r[ri++]);
    return p;
  }
};

template<class S, class T=long long>
struct merge_sort_tree_sum : public merge_sort_tree<S> {
  merge_sort_tree_sum(const vector<S>& data) : merge_sort_tree<S>(data) {
    /* O(n log n) */
    int tree_size = 2 * this->leafs;
    node_csum = vector<vector<T>>(tree_size);
    for(int i=0; i<tree_size; i++) {
      vector<S> &nd = this->node[i];
      vector<T> &csum = node_csum[i];
      csum.resize(nd.size()+1);
      csum[0] = 0;
      for(int j=0; j<ssize(this->node[i]); ++j)
        csum[j+1] = csum[j] + nd[j];
    }
  }

  T sum(int l, int r, S low, S high) { // [l, r), [low, high)
    /* O(log^2 n) */
    /* sum of data[i] s.t low <= data[i] < high && l <= i < r */
    assert(0 <= l && l <= r && r <= this->n);
    assert(low <= high);
    T total = 0;
    for(int i : this->extract_nodes(l, r)) {
      vector<S> &nd = this->node[i];
      vector<T> &csum = this->node_csum[i];
      int li = lower_bound(nd.begin(), nd.end(), low) - nd.begin();
      int ri = lower_bound(nd.begin(), nd.end(), high) - nd.begin();
      total += csum[ri] - csum[li]; /* [li, ri) */
    }
    return total;
  }

  private:
  vector<vector<long long>> node_csum;
};

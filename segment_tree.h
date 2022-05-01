template <class S, S (*op)(S, S), S (*e)()> struct segment_tree {
  int n, leafs;
  vector<S> node;

  segment_tree(int n=0) : segment_tree(vector<S>(n, e())) {}
  segment_tree(const vector<S>& initial) : n(int(initial.size())) {
    /* O(n) */
    int msb = 1; while((msb<<1) <= n) msb <<= 1;
    leafs = (n==msb) ? n : msb << 1;
    node = vector<S>(2 * leafs - 1, e());
    for(int i=0; i<n; i++) node[i+leafs-1] = initial[i];
    for(int i=leafs-2; i>=0; --i) node[i] = op(node[l_child(i)], node[r_child(i)]);
  }

  static inline int r_child(int v) { return v*2+2; }
  static inline int l_child(int v) { return v*2+1; }
  static inline int parent(int v) { return (v+1)/2-1; }

  S product(int l, int r, int v=0, int vl=0, int vr=-1) { /* [l, r) */
    /* O(log n) */
    assert(l >=0 && l <= n);
    assert(r >=0 && r <= n);
    assert(l <= r); // return e() if l==r
    vr = (vr==-1) ? leafs : vr;
    if(l <= vl && vr <= r) return node[v];
    S ret = e(); int mid=(vl+vr)/2;
    if(l < mid) ret = op(product(l, r, l_child(v), vl, mid),ret);
    if(r > mid) ret = op(ret,product(l, r, r_child(v), mid, vr));
    return ret;
  }

  void set(int index, S s) {
    /* O(log n) */
    assert(0 <= index && index < n);
    int v = index + (leafs-1);
    node[v] = s;
    while((v=parent(v)) != -1) node[v] = op(node[l_child(v)], node[r_child(v)]);
  }
  S get(int index) {
    assert(0 <= index && index < n);
    return node[index + (leafs-1)];
  }

  int max_right(int l, function<bool(S)> f) const {
    /* O(log n) */
    // returns r such that
    //         f(op(a[l], a[l + 1], ..., a[r - 1])) == true
    //         f(op(a[l], a[l + 1], ..., a[r])) == false
    assert(0 <= l && l <= n);
    assert(f(e()));
    if (l == n) return n;
    int v = l + (leafs-1);
    S sm = e();
    do {
      while (v % 2 == 1) v = parent(v);
      if (!f(op(sm, node[v]))) {
        while (v < leafs-1) {
          v = l_child(v);
          if (f(op(sm, node[v]))) {
            sm = op(sm, node[v]);
            v++;
          }
        }
        return v - (leafs-1);
      }
      sm = op(sm, node[v]);
      v++;
    } while (((v+1) & -(v+1)) != (v+1));
    return n;
  }

  int min_left(int r, function<bool(S)> f) const {
    /* O(log n) */
    // returns l such that
    //         f(op(a[l], a[l + 1], ..., a[r - 1])) == true
    //         f(op(a[l - 1], a[l], ..., a[r - 1])) == false
    assert(0 <= r && r <= n);
    assert(f(e()));
    if (r == 0) return 0;
    int v = r + (leafs-1);
    S sm = e();
    do {
      v--;
      while (v > 0 && (v % 2 == 0)) v = parent(v);
      if (!f(op(node[v], sm))) {
        while (v < leafs-1) {
          v = r_child(v);
          if (f(op(node[v], sm))) {
            sm = op(node[v], sm);
            v--;
          }
        }
        return v + 1 - (leafs-1);
      }
      sm = op(node[v], sm);
    } while (((v+1) & -(v+1)) != (v+1));
    return 0;
  }
};

#if 0 /* Range Min */
using S = int;
S op(S a, S b) { return min(a, b); }
S e() { return 1e9; }
#endif

#if 0 /* Range Sum */
using S = int;
S op(S a, S b) { return a + b; }
S e() { return 0; }
#endif

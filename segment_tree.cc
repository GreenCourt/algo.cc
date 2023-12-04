template <class S, S (*op)(S, S), S (*e)()> struct segment_tree {
  segment_tree(int n=0) : segment_tree(vector<S>(n, e())) {}
  segment_tree(const vector<S>& initial) : n(int(initial.size())) {
    /* O(n) */
    int msb = 1; while((msb<<1) <= n) msb <<= 1;
    leafs = (n==msb) ? n : msb << 1;
    node = vector<S>(2 * leafs, e());
    for(int i=0; i<n; i++) node[i+leafs] = initial[i];
    for(int i=leafs-1; i>0; --i) node[i] = op(node[l_child(i)], node[r_child(i)]);
  }

  S product(int l, int r) { /* [l, r) */
    /* O(log n) */
    assert(0 <= l && l <= r && r <= n); // return e() if l==r
    S pl = e(), pr = e();
    l += leafs, r += leafs;
    while(l < r) {
      if(l & 1) pl = op(pl, node[l++]);
      if(r & 1) pr = op(node[--r], pr);
      l = parent(l), r = parent(r);
    }
    return op(pl, pr);
  }

  void set(int index, S s) {
    /* O(log n) */
    assert(0 <= index && index < n);
    int v = index + leafs;
    node[v] = s;
    while((v=parent(v))) node[v] = op(node[l_child(v)], node[r_child(v)]);
  }

  S get(int index) {
    assert(0 <= index && index < n);
    return node[index + leafs];
  }

  int max_right(int l, function<bool(S)> f) const {
    /* O(log n) */
    // returns r such that
    //         f(op(a[l], a[l + 1], ..., a[r - 1])) == true
    //         f(op(a[l], a[l + 1], ..., a[r])) == false
    assert(0 <= l && l <= n);
    assert(f(e()));
    if (l == n) return n;
    int v = l + leafs;
    S sm = e();
    do {
      while (v % 2 == 0) v = parent(v);
      if (!f(op(sm, node[v]))) {
        while (v < leafs) {
          v = l_child(v);
          if (f(op(sm, node[v]))) {
            sm = op(sm, node[v]);
            v++;
          }
        }
        return v - leafs;
      }
      sm = op(sm, node[v]);
      v++;
    } while ((v & -v) != v);
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
    int v = r + leafs;
    S sm = e();
    do {
      v--;
      while (v > 1 && (v % 2)) v = parent(v);
      if (!f(op(node[v], sm))) {
        while (v < leafs) {
          v = r_child(v);
          if (f(op(node[v], sm))) {
            sm = op(node[v], sm);
            v--;
          }
        }
        return v + 1 - leafs;
      }
      sm = op(node[v], sm);
    } while ((v & -v) != v);
    return 0;
  }
  private:
  int n, leafs;
  vector<S> node;
  static inline int r_child(int v) { return v*2+1; }
  static inline int l_child(int v) { return v*2; }
  static inline int parent(int v) { return v/2; }
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

#if 0 /* Range gcd */
using S = int;
S op(S a, S b) { return gcd(a, b); }
S e() { return 0; }
#endif

#if 0 /* Rolling hash */
/*
 *  pow_base must be initialized by base like vector<S>(n, {0,base})
 */
long long base = 100000007, mod = 1000000007;
struct S { long long hash, pow_base; };
S op(S a, S b) { return { (a.hash * b.pow_base % mod + b.hash) % mod, a.pow_base * b.pow_base % mod}; }
S e() { return {0, 1}; }
#endif

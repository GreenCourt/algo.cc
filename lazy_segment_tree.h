template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segment_tree {
  int n, leafs;
  vector<S> node;
  vector<F> lazy;

  lazy_segment_tree(int n=0) : lazy_segment_tree(vector<S>(n, e())) {}
  lazy_segment_tree(const vector<S>& initial) : n(int(initial.size())) {
    /* O(n) */
    int msb = 1; while((msb<<1) <= n) msb <<= 1;
    leafs = (n==msb) ? n : msb << 1;
    node = vector<S>(2 * leafs - 1, e());
    lazy = vector<F>(2 * leafs - 1, id());
    for(int i=0; i<n; i++) node[i+leafs-1] = initial[i];
    for(int i=leafs-2; i>=0; --i) node[i] = op(node[l_child(i)], node[r_child(i)]);
  }

  inline int r_child(int v) { return v*2+2; }
  inline int l_child(int v) { return v*2+1; }
  inline int parent(int v) { return (v+1)/2-1; }
  inline bool is_leaf(int v) { return v >= (leafs-1); }

  void lazy_update(int v) { 
    /* O(1) */
    node[v] = mapping(lazy[v], node[v]);
    if ( !is_leaf(v) ) {
      lazy[l_child(v)] = composition(lazy[v], lazy[l_child(v)]);
      lazy[r_child(v)] = composition(lazy[v], lazy[r_child(v)]);
    }
    lazy[v] = id();
  }

  S product(int l, int r, int v=0, int vl=0, int vr=-1) { /* [l, r) */
    /* O(log n) */
    assert(l >=0 && l <= n);
    assert(r >=0 && r <= n);
    assert(l <= r); // return e() if l==r
    vr = (vr==-1) ? leafs : vr;
    lazy_update(v);
    if(l<=vl && vr<=r) return node[v];
    S ret = e(); int mid=(vl+vr)/2;
    if(l < mid) ret = op(product(l, r, l_child(v), vl, mid),ret);
    if(r > mid) ret = op(ret,product(l, r, r_child(v), mid, vr));
    return ret;
  }

  void apply(int l, int r, F f, int v=0, int vl=0, int vr=-1) { /* [l, r) */
    /* O(log n) */
    assert(l >=0 && l <= n);
    assert(r >=0 && r <= n);
    assert(l <= r); // nop if l==r
    vr = (vr==-1) ? leafs : vr;
    lazy_update(v);
    if(l >= vr || r <= vl) return;
    if(l<=vl && vr<=r) {
      lazy[v] = composition(f, lazy[v]);
      lazy_update(v);
    }
    else {
      int mid=(vl+vr)/2;
      apply(l, r, f, l_child(v), vl, mid);
      apply(l, r, f, r_child(v), mid, vr);
      node[v] = op(node[l_child(v)], node[r_child(v)]);
    }
  }

  void lazy_update_all_ancestors(int v) {
    /* O(log n) */
    vector<int> path_to_root;
    for(int u = parent(v); u != -1; u=parent(u)) path_to_root.push_back(u);
    for(auto itr = rbegin(path_to_root); itr != rend(path_to_root); ++itr) lazy_update(*itr);
  }

  void set(int index, S s) {
    /* O(log n) */
    assert(0 <= index && index < n);
    int v = index + (leafs-1);
    lazy_update_all_ancestors(v);
    node[v] = s;
    while((v=parent(v)) != -1) node[v] = op(node[l_child(v)], node[r_child(v)]);
  }

  S get(int index) {
    /* O(log n) */
    assert(0 <= index && index < n);
    int v = index + (leafs-1);
    lazy_update_all_ancestors(v);
    lazy_update(v);
    return node[v];
  }
};


#if 0 /* Range Minimum, Range Add */
using S = long long;
using F = long long;
const S INF = 1e18;
S op(S l, S r){ return min(l, r); }
S e(){ return INF; }
S mapping(F f, S s){ return f+s; }
F composition(F f, F g){ return f+g; } // f.g = f(g(s))
F id(){ return 0; }
#endif

#if 0 /* Range Max, Range Add */
using S = long long;
using F = long long;
const S INF = 1e18;
S op(S l, S r){ return max(l, r); }
S e(){ return -INF; }
S mapping(F f, S s){ return f+s; }
F composition(F f, F g){ return f+g; } // f.g = f(g(s))
F id(){ return 0; }
#endif

#if 0 /* Range Minimum, Range Update */
using S = long long;
using F = long long;
const S INF = 1e18;
const F ID = 1e18;
S op(S l, S r){ return min(l, r); }
S e(){ return INF; }
S mapping(F f, S s){ return (f == ID ? s : f); }
F composition(F f, F g){ return (f == ID ? g : f); } // f.g = f(g(s))
F id(){ return ID; } 
#endif

#if 0 /* Range Max, Range Update */
using S = long long;
using F = long long;
const S INF = 1e18;
const F ID = 1e18;
S op(S l, S r){ return max(l, r); }
S e(){ return -INF; }
S mapping(F f, S s){ return (f == ID ? s : f); }
F composition(F f, F g){ return (f == ID ? g : f); } // f.g = f(g(s))
F id(){ return ID; }
#endif

#if 0 /* Range Sum, Range Update */
struct S{ long long value; int size; };
using F = long long;
const F ID = 1e18;
S op(S l, S r){ return {l.value+r.value, l.size+r.size}; }
S e(){ return {0, 0}; }
S mapping(F f, S s){ if(f != ID) s.value = f*s.size; return s; }
F composition(F f, F g){ return (f == ID ? g : f); } // f.g = f(g(s))
F id(){ return ID; }
#endif

#if 0 /* Range Sum, Range Add */
struct S{ long long value; int size; };
using F = long long;
S op(S l, S r){ return {l.value+r.value, l.size+r.size}; }
S e(){ return {0, 0}; }
S mapping(F f, S s){ return {s.value + f*s.size, s.size}; }
F composition(F f, F g){ return f+g; } // f.g = f(g(s))
F id(){ return 0; }
#endif

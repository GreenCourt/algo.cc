template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segment_tree {
  lazy_segment_tree(int n=0) : lazy_segment_tree(vector<S>(n, e())) {}
  lazy_segment_tree(const vector<S>& initial) : n(int(initial.size())) {
    /* O(n) */
    int msb = 1;
    height = 1;
    while((msb<<1) <= n) msb <<= 1, height++;
    leafs = (n==msb) ? n : msb << 1;
    node = vector<S>(2 * leafs, e());
    lazy = vector<F>(leafs, id());
    for(int i=0; i<n; i++) node[i+leafs] = initial[i];
    for(int i=leafs-1; i>0; --i) update_from_children(i);
  }
  S product(int l, int r) { /* [l, r) */
    /* O(log n) */
    assert(0 <= l && l <= r && r <= n);
    if(l == r) return e();
    S pl = e(), pr = e();
    l += leafs, r += leafs;
    for(int i=height; i>0; i--) {
      if(((l>>i) << i) != l) push2children(l>>i);
      if(((r>>i) << i) != r) push2children(r>>i);
    }
    while(l<r) {
      if(l & 1) pl = op(pl, node[l++]);
      if(r & 1) pr = op(node[--r], pr);
      l = parent(l), r = parent(r);
    }
    return op(pl, pr);
  }
  void apply(int l, int r, F f) { /* [l, r) */
    /* O(log n) */
    assert(0 <= l && l <= r && r <= n); // nop if l==r
    if(l==r) return;
    l += leafs, r += leafs;
    for(int i=height; i>0; i--) {
      if(((l>>i) << i) != l) push2children(l>>i);
      if(((r>>i) << i) != r) push2children((r-1)>>i);
    }
    for(int L=l, R=r; L<R; L=parent(L), R=parent(R)) {
      if (L & 1) push(L++, f);
      if (R & 1) push(--R, f);
    }
    for(int i=1; i<=height; i++) {
      if(((l>>i) << i) != l) update_from_children(l>>i);
      if(((r>>i) << i) != r) update_from_children((r-1)>>i);
    }
  }
  void set(int index, S s) {
    /* O(log n) */
    assert(0 <= index && index < n);
    int v = index + leafs;
    for(int i=height; i>0; i--) push2children(v>>i); // push from root to v
    node[v] = s;
    while((v=parent(v))) node[v] = op(node[l_child(v)], node[r_child(v)]);
  }
  S get(int index) {
    /* O(log n) */
    assert(0 <= index && index < n);
    int v = index + leafs;
    for(int i=height; i>0; i--) push2children(v>>i); // push from root to v
    return node[v];
  }
  int max_right(int l, function<bool(S)> f) {
    /* O(log n) */
    // returns r such that
    //         f(op(a[l], a[l + 1], ..., a[r - 1])) == true
    //         f(op(a[l], a[l + 1], ..., a[r])) == false
    assert(0 <= l && l <= n);
    assert(f(e()));
    if(l==n) return n;
    int v = l + leafs;
    for(int i=height; i>0; i--) push2children(v>>i);
    S sm = e();
    do {
      while(v % 2 == 0) v = parent(v);
      if(!f(op(sm, node[v]))) {
        while (v < leafs) {
          push2children(v);
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

  int min_left(int r, function<bool(S)> f) {
    /* O(log n) */
    // returns l such that
    //         f(op(a[l], a[l + 1], ..., a[r - 1])) == true
    //         f(op(a[l - 1], a[l], ..., a[r - 1])) == false
    assert(0 <= r && r <= n);
    assert(f(e()));
    if(r==0) return 0;
    int v = r + leafs;
    for(int i=height; i>0; i--) push2children((v-1)>>i);
    S sm = e();
    do {
      v--;
      while (v > 1 && (v % 2)) v = parent(v);
      if (!f(op(node[v], sm))) {
        while (v < leafs) {
          push2children(v);
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
  int n, leafs, height;
  vector<S> node;
  vector<F> lazy;
  inline int r_child(int v) { return v*2+1; }
  inline int l_child(int v) { return v*2; }
  inline int parent(int v) { return v/2; }
  inline bool is_leaf(int v) { return v >= leafs; }
  inline void push(int v, F f) {
    node[v] = mapping(f, node[v]);
    if(!is_leaf(v)) lazy[v] = composition(f, lazy[v]);
  }
  inline void push2children(int v) { 
    if(is_leaf(v)) return;
    push(l_child(v), lazy[v]);
    push(r_child(v), lazy[v]);
    lazy[v] = id();
  }
  inline void update_from_children(int v) { 
    node[v] = op(node[l_child(v)], node[r_child(v)]);
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
/*
 *  size must be initialized by 1 like vector<S>(n, {0,1})
 */
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
/*
 *  size must be initialized by 1 like vector<S>(n, {0,1})
 */
struct S{ long long value; int size; };
using F = long long;
S op(S l, S r){ return {l.value+r.value, l.size+r.size}; }
S e(){ return {0, 0}; }
S mapping(F f, S s){ return {s.value + f*s.size, s.size}; }
F composition(F f, F g){ return f+g; } // f.g = f(g(s))
F id(){ return 0; }
#endif

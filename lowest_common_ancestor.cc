template<typename T>
struct SparseTable {
  vector<vector<T>> st;
  vector<int> lg;
  SparseTable() = default;
  SparseTable(const vector<T> &init) { /* O(n log n) */
    int b = 0;
    while((1 << b) <= ssize(init)) ++b;
    st.assign(b, vector<T>(1 << b));
    for(int i = 0; i < ssize(init); i++) st[0][i] = init[i];
    for(int i = 1; i < b; i++) for(int j = 0; j + (1 << i) <= (1 << b); j++) 
      st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    lg.resize(init.size() + 1);
    for(int i = 2; i < ssize(lg); i++) lg[i] = lg[i >> 1] + 1;
  }
  inline T rmq(int l, int r) { /* O(1) */
    assert(l<r);
    int b = lg[r - l];
    return min(st[b][l], st[b][r - (1 << b)]);
  }
};

struct LowestCommonAncestor {
  using edge = int;
  vector<int> first_appear;
  vector<pair<int,int>> eular_tour; /* (depth, vertex) */
  SparseTable<pair<int,int>> st;
  vector<int> depth, parent;
  LowestCommonAncestor(const vector<vector<edge>>& adj, int root = 0) { /* O(n log n) */
    int n = ssize(adj); if(n==0) return;
    depth.assign(n, -1);
    parent.assign(n, -1);
    first_appear.assign(n, -1);
    eular_tour.reserve(2*n-1);
    dfs(root, 0, adj);
    st = SparseTable(eular_tour);
  }
  int lca(int u, int v) { /* O(1) */
    int l = min(first_appear[u], first_appear[v]);
    int r = max(first_appear[u], first_appear[v])+1;
    return st.rmq(l,r).second;
  }
  int distance(int u, int v) { /* O(1) */
    int x = lca(u,v);
    return depth[u] + depth[v] - 2 * depth[x];
  }
  vector<int> path(int from, int to) { /* O(path_length) */
    int x = lca(from, to), u;
    vector<int> p1, p2;
    p1.push_back(u = from);
    while(u!=x) p1.push_back(u = parent[u]);
    p2.push_back(u = to);
    while(u!=x) p2.push_back(u = parent[u]);
    for(auto it = next(p2.rbegin()); it!=p2.rend(); it++) p1.push_back(*it);
    return p1;
  }
  private:
  void dfs(int v, int d, const vector<vector<edge>>& adj) {
    first_appear[v] = ssize(eular_tour), depth[v] = d;
    eular_tour.emplace_back(d, v);
    for(int u : adj[v]) if(first_appear[u] == -1) {
      parent[u] = v;
      dfs(u, d+1, adj); eular_tour.emplace_back(d, v);
    }
  }
};

vector<int> detect_one_cycle(const vector<vector<int>> &adj, bool directed) {
  /* O(|V| + |E|) */
  int n = adj.size();
  vector<int> parent(n, -1);
  vector<bool> mark(n, false);
  stack<pair<int,int>> dfs;
  for(int s=0; s<n; ++s) {
    if(parent[s] != -1) continue;
    dfs.emplace(~s,s);
    dfs.emplace(s,s);
    while(dfs.size()) {
      auto [v,p] = dfs.top(); dfs.pop();
      if(v>=0) {
        parent[v] = p;
        mark[v] = true;
        for(auto it=adj[v].rbegin(); it!=adj[v].rend(); ++it) {
          int u = *it;
          if(!directed && u==p) continue;
          if(mark[u]) {
            // cycle detected
            vector<int> cycle;
            while(v!=u) {
              cycle.push_back(v);
              v = parent[v];
            }
            cycle.push_back(u);
            reverse(cycle.begin(), cycle.end());
            return cycle;
          }
          if(parent[u] != -1) continue;
          dfs.emplace(~u,v);
          dfs.emplace(u,v);
        }
      } else { // dfs backword
        v = ~v;
        assert((parent[v] == p && mark[v]) || (parent[v] != p && !mark[v]));
        mark[v] = false;
      }
    }
  }
  return vector<int>(); // cycle not found
}

vector<vector<int>> detect_all_cycles_in_functional_graph(const vector<int> &adj) {
  /* O(|V|) */
  int n = adj.size();
  vector<int> mark(n, -1);
  vector<vector<int>> cycles;
  for(int s=0; s<n; ++s) {
    if(mark[s] != -1) continue;
    int v = s;
    mark[v] = s;
    int u;
    while(mark[u=adj[v]] == -1) mark[v=u] = s;
    if(mark[u] != s) continue;
    int stop = u;
    cycles.push_back(vector<int>());
    vector<int> &c = cycles.back();
    c.push_back(u);
    while(adj[u]!=stop) c.push_back(u = adj[u]);
  }
  return cycles;
}

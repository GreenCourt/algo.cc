struct CycleDetection {
  bool has_cycle = false;
  vector<int> cycle; /* first found only */

  CycleDetection(const vector<vector<int>> &adj) : adj(adj) {
    /* O(|V| + |E|) */
    int n = adj.size();
    mark = vector(n, -1);
    visited = vector(n, false);
    for(int v=0; v<n; ++v) {
      if(visited[v]) continue;
      mark[v] = path.size();
      path.push_back(v);
      dfs(v);
      mark[v] = -1;
      path.pop_back();
      if(has_cycle) break;
    }
  }

  private:
  const vector<vector<int>> &adj;
  vector<bool> visited;
  vector<int> mark, path;
  void dfs(int v, int p=-1) {
    visited[v] = true;
    for(int u:adj[v]) if(u!=p) {
      if(mark[u] != -1) {
        has_cycle = true;
        for(int i=mark[u]; i<path.size(); ++i) cycle.push_back(path[i]);
        return;
      }
      if(visited[u]) continue;
      mark[u] = path.size();
      path.push_back(u);
      dfs(u,v);
      mark[u] = -1;
      path.pop_back();
      if(has_cycle) return;
    }
  }
};

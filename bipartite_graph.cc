struct BipartiteGraph {
  /* vectors become empty if failed to construct bipartite graph */
  vector<int> color; // 0 or 1 for each vertex
  vector<vector<int>> connected_components;
  vector<int> component_number; // for each vertex

  BipartiteGraph(const vector<vector<int>> &adj) {
    /* O(|V| + |E|) */
    int n = adj.size();
    color = vector<int>(n, -1);
    for(int i = 0; i<n; ++i) if(color[i] == -1) {
      connected_components.push_back({i});
      vector<int> &g = connected_components.back();
      color[i] = 0;
      queue<int> q({i});
      while (q.size()) {
        int v = q.front(); q.pop();
        for(int u : adj[v]) {
          if(color[v] == color[u]) {
            // failed to construct bipartite graph
            color.clear();
            connected_components.clear();
            component_number.clear();
            return;
          }
          if(color[u] != -1) continue;
          g.push_back(u);
          color[u] = !color[v];
          q.push(u);
        }
      }
    }
  }
};

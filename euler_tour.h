struct EulerTour {
  const vector<vector<int>> &adj;
  vector<int> tour, first_visit, last_visit;
  int length = 0;
  void touch (int v) {
    if(first_visit[v] == -1) first_visit[v] = length;
    last_visit[v] = length;
    length++;
    tour.push_back(v);
  };
  void dfs(int v, int p=-1) {
    touch(v);
    for(int u : adj[v]) if(u!=p && first_visit[u]==-1) {
      dfs(u, v);
      touch(v);
    }
  }
  EulerTour(const vector<vector<int>> &adj, int root) : adj(adj),
    first_visit(vector<int>(adj.size(), -1)),
    last_visit(vector<int>(adj.size(), -1))
  {
    /* O(|V| + |E|) */
    dfs(root);
  }
};

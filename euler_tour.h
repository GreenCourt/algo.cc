struct EulerTour {
  vector<int> tour, first_visit, last_visit;
  EulerTour(const vector<vector<int>> &adj, int root) :
    first_visit(vector<int>(adj.size(), -1)),
    last_visit(vector<int>(adj.size(), -1)),
    adj(adj)
  {
    /* O(|V| + |E|) */
    dfs(root);
  }
  private:
  const vector<vector<int>> &adj;
  void touch (int v) {
    if(first_visit[v] == -1) first_visit[v] = tour.size();
    last_visit[v] = tour.size();
    tour.push_back(v);
  };
  void dfs(int v, int p=-1) {
    touch(v);
    for(int u : adj[v]) if(u!=p && first_visit[u]==-1) {
      dfs(u, v);
      touch(v);
    }
  }
};

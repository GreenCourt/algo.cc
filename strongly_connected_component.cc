struct StronglyConnectedComponent {
  vector<int> group_number;   // for each vertex
  vector<vector<int>> groups; // Each group is a strongly connected component.
                              // Weakly connected groups are topologically sorted.
                              // Ordering between disconnected groups is not guaranteed.
                              // e.g.
                              //
                              //    -----------------------
                              //    |                     |
                              //    |                     v
                              // groups[0]  groups[1]  groups[2] --> group[3]  group[4]
                              //               |                                  ^
                              //               |                                  |
                              //               ------------------------------------
                              //
  StronglyConnectedComponent(const vector<vector<int>>& adj_) : n(ssize(adj_)), adj(adj_) {
    /* O(|V|+|E|) */
    post_order.reserve(n); visited.assign(n,false);
    for(int v=0;v<n; ++v) if(!visited[v]) dfs(v);
    radj.resize(n);
    for(int v=0; v<n; ++v) for(int u:adj[v]) radj[u].push_back(v);
    group_number.assign(n,-1);
    for(auto it=post_order.rbegin(); it!=post_order.rend(); it++) if(group_number[*it]==-1) {
      groups.emplace_back();
      rdfs(*it);
    }
  }
  private:
  const int n;
  const vector<vector<int>>& adj;
  vector<vector<int>> radj;
  vector<bool> visited;
  vector<int> post_order;
  void dfs(int v) {
    visited[v] = true;
    for(int u : adj[v]) if(!visited[u]) dfs(u);
    post_order.push_back(v);
  }
  void rdfs(int v) {
    group_number[v] = ssize(groups)-1;
    groups.back().push_back(v);
    for(int u : radj[v]) if(group_number[u]==-1) rdfs(u);
  }
};

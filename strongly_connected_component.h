struct StronglyConnectedComponent {
  vector<vector<int>> groups; // topologically sorted groups
  vector<int> group_number;   // for each vertex
  /* ------------------------ */
  const int n;
  const vector<vector<int>>& adj;
  vector<vector<int>> radj;
  vector<bool> visited;
  vector<int> order;
  void dfs(int v) {
    visited[v] = true;
    for(int u : adj[v]) if(!visited[u]) dfs(u);
    order.push_back(v);
  }
  void rdfs(int v) {
    group_number[v] = groups.size()-1;
    groups.back().push_back(v);
    for(int u : radj[v]) if(group_number[u]==-1) rdfs(u);
  }
  StronglyConnectedComponent(const vector<vector<int>>& adj) : n(adj.size()), adj(adj) {
    /* O(|V|+|E|) */
    order.reserve(n); visited.assign(n,false);
    for(int v=0;v<n; ++v) if(!visited[v]) dfs(v);
    radj.resize(n);
    for(int v=0; v<n; ++v) for(int u:adj[v]) radj[u].push_back(v);
    group_number.assign(n,-1);
    for(auto it=order.rbegin(); it!=order.rend(); it++) if(group_number[*it]==-1) {
      groups.emplace_back();
      rdfs(*it);
    }
  }
};

struct FordFulkerson {
  const static long long INF=numeric_limits<long long>::max()/2;
  int n;
  struct edge {int from, to; long long capacity, flow;};
  vector<edge> edges, backward_edges;
  vector<vector<int>> adj_forward, adj_backward;

  FordFulkerson(int n_ = 0) : n(n_), adj_forward(n_), adj_backward(n_) { }

  int add_edge(int from, int to, long long capacity) {
    /* O(1) */
    int index = ssize(edges);
    adj_forward[from].push_back(index);
    adj_backward[to].push_back(index);
    edges.push_back({from, to, capacity, 0});
    backward_edges.push_back({to, from, 0, 0});
    return index;
  }

  long long maxflow(int s, int t) {
    /* O(|E|f)  f=maxflow */
    long long flow = 0;
    vector<bool> visited(n);
    while(true) {
      visited.assign(n, false);
      long long f = dfs(s, visited, t);
      if(f==0) return flow;
      flow += f;
    }
    return 0; // dummy
  }

  private:
  long long dfs(int v, vector<bool> &visited, int t, long long flow=INF) {
    /* O(|E|) */
    if(v==t) return flow;
    visited[v] = true;
    for(int i : adj_forward[v]) {
      edge& e = edges[i];
      if(visited[e.to]) continue;
      if(e.capacity - e.flow == 0) continue;
      long long f = dfs(e.to, visited, t, min(flow, e.capacity - e.flow));
      if (f == 0) continue;
      e.flow += f;
      backward_edges[i].flow -= f;
      return f;
    }
    for(int i : adj_backward[v]) {
      edge& e = backward_edges[i];
      if(visited[e.to]) continue;
      if(e.capacity - e.flow == 0) continue;
      long long f = dfs(e.to, visited, t, min(flow, e.capacity - e.flow));
      if (f == 0) continue;
      e.flow += f;
      edges[i].flow -= f;
      return f;
    }
    return 0;
  }
};

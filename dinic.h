struct Dinic {
  const long long INF=1e18;
  int n;
  struct edge {int from, to; long long capacity, flow;};
  vector<edge> edges, backward_edges;
  vector<vector<int>> adj_forward, adj_backward;
  vector<int> level;

  Dinic(int n = 0) : n(n), adj_forward(n), adj_backward(n), level(n) { }

  int add_edge(int from, int to, long long capacity) {
    /* O(1) */
    int index = edges.size();
    adj_forward[from].push_back(index);
    adj_backward[to].push_back(index);
    edges.push_back({from, to, capacity, 0});
    backward_edges.push_back({to, from, 0, 0});
    return index;
  }

  long long maxflow(int s, int t) {
    /* O(|V|^2 |E|) */
    long long flow = 0, f;
    while(bfs(s,t)) while (f=dfs(s,t)) flow += f;
    return flow;
  }

  private:
  bool bfs(int s, int t) {
    /* O(|E|) */
    level.assign(n, -1);
    level[s] = 0;
    queue<int> q;
    q.push(s);
    while(q.size()) {
      int v = q.front(); q.pop();
      for(int i : adj_forward[v]) {
        edge& e = edges[i];
        if(level[e.to] != -1) continue;
        if(e.capacity - e.flow == 0) continue;
        level[e.to] = level[v] + 1;
        q.push(e.to);
      }
      for(int i : adj_backward[v]) {
        edge& e = backward_edges[i];
        if(level[e.to] != -1) continue;
        if(e.capacity - e.flow == 0) continue;
        level[e.to] = level[v] + 1;
        q.push(e.to);
      }
    }
    return level[t] != -1;
  }

  long long dfs(int v, int t, long long flow=1e18) {
    /* O(|E|) */
    if(v==t) return flow;
    for(int i : adj_forward[v]) {
      edge& e = edges[i];
      if(level[e.to] <= level[v]) continue;
      if(e.capacity - e.flow == 0) continue;
      long long f = dfs(e.to, t, min(flow, e.capacity - e.flow));
      if (f == 0) continue;
      e.flow += f;
      backward_edges[i].flow -= f;
      return f;
    }
    for(int i : adj_backward[v]) {
      edge& e = backward_edges[i];
      if(level[e.to] <= level[v]) continue;
      if(e.capacity - e.flow == 0) continue;
      long long f = dfs(e.to, t, min(flow, e.capacity - e.flow));
      if (f == 0) continue;
      e.flow += f;
      edges[i].flow -= f;
      return f;
    }
    return 0;
  }
};


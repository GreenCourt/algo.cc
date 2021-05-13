struct edge {int u, weight;};
tuple<long long,int,int> tree_diameter(const vector<vector<edge>>& adj) {
  /* O(|V|+|E|) */
  // return diameter and two vertices s and t where dist(s,t) = diameter.
  int n = adj.size();
  int s, t; long long diameter;
  {
    vector<long long> dist(n, -1); dist[0] = 0;
    stack<int> st; st.push(0);
    pair<long long,int> x = {-1, -1};
    while(st.size()) {
      int v = st.top(); st.pop();
      x = max(x, {dist[v] ,v});
      for(auto [u,w]:adj[v]) if(dist[u] == -1) {
        dist[u] = dist[v] + w;
        st.push(u);
      }
    }
    s = x.second;
  }
  {
    vector<long long> dist(n, -1); dist[s] = 0;
    stack<int> st; st.push(s);
    pair<long long,int> x = {-1, -1};
    while(st.size()) {
      int v = st.top(); st.pop();
      x = max(x, {dist[v] ,v});
      for(auto [u,w]:adj[v]) if(dist[u] == -1) {
        dist[u] = dist[v] + w;
        st.push(u);
      }
    }
    t = x.second;
    diameter = x.first;
  }
  return {diameter, s, t};
}

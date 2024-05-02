struct edge {int u, weight;};
struct tree_diameter {
  long long diameter;
  int a,b; // vertices where dist(a,b) = diameter
  vector<long long> dist_from_a;

  tree_diameter(const vector<vector<edge>>& adj) {
    /* O(|V|+|E|) */
    int n = ssize(adj);
    {
      vector<long long> dist_from_0(n, -1); dist_from_0[0] = 0;
      stack<int> st; st.push(0);
      pair<long long,int> x = {-1, -1};
      while(st.size()) {
        int v = st.top(); st.pop();
        x = max(x, {dist_from_0[v] ,v});
        for(auto [u,w]:adj[v]) if(dist_from_0[u] == -1) {
          dist_from_0[u] = dist_from_0[v] + w;
          st.push(u);
        }
      }
      a = x.second;
    }

    dist_from_a = vector<long long>(n, -1);
    dist_from_a[a] = 0;
    stack<int> st; st.push(a);
    pair<long long,int> x = {-1, -1};
    while(st.size()) {
      int v = st.top(); st.pop();
      x = max(x, {dist_from_a[v] ,v});
      for(auto [u,w]:adj[v]) if(dist_from_a[u] == -1) {
        dist_from_a[u] = dist_from_a[v] + w;
        st.push(u);
      }
    }
    b = x.second;
    diameter = x.first;
  }
};

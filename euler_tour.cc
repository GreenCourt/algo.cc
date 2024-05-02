struct EulerTour {
  vector<int> tour, first_visit, last_visit;
  EulerTour(const vector<vector<int>> &adj, int root) :
    first_visit(vector<int>(adj.size(), -1)),
    last_visit(vector<int>(adj.size(), -1))
  {
    /* O(|V| + |E|) */
    stack<pair<int,int>> dfs;
    dfs.emplace(~root,-1);
    dfs.emplace(root,-1);
    while(dfs.size()) {
      auto [v,p] = dfs.top(); dfs.pop();
      if(v>=0) {
        if(first_visit[v] != -1) continue;
        first_visit[v] = last_visit[v] = ssize(tour);
        tour.push_back(v);
        for(auto it=adj[v].rbegin(); it!=adj[v].rend(); it++) if(first_visit[*it]==-1) {
          dfs.emplace(~*it,v);
          dfs.emplace(*it,v);
        }
      } else {
        v = ~v;
        int parent_of_v = (v==root) ? -1 : tour[first_visit[v]-1];
        if(v != root && parent_of_v == p) { // post process to parent
          last_visit[p] = ssize(tour);
          tour.push_back(p);
        }
      }
    }
  }
};

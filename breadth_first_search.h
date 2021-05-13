vector<int> distance_by_bfs(vector<vector<int>> &adjlist, int start) {
  /* O(|E|) */
  queue<int> q;
  vector<int> dist(adjlist.size(), -1);
  dist[start] = 0;
  q.push(start);
  while (q.size()) {
    int v = q.front(); q.pop();
    for(int u : adjlist[v]) {
      if(dist[u] != -1) continue;
      dist[u] = dist[v] + 1;
      q.push(u);
    }
  }
  return dist;
}

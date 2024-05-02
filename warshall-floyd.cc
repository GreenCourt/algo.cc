const long long INF = numeric_limits<long long>::max()/2;
vector<vector<long long>> warshall_floyd(vector<vector<long long>> const &adjmatrix) {
  /* O(|V|^3) */
  int n = ssize(adjmatrix);
  for(int i=0; i<n; ++i) assert(adjmatrix[i][i]==0);
  vector<vector<long long>> dist(adjmatrix);
  for(int k = 0; k < n; ++k)
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; ++j)
        if(dist[i][k]!=INF && dist[k][j]!=INF)
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
  return dist;
}

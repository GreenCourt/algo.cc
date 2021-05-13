const long long INF = numeric_limits<long long>::max()/2;
struct edge {int from, to; int dist;};
vector<long long> bellman_ford(int source, int n, const vector<edge> &edges) {
  /* O(|V||E|) */
  vector<long long> dist(n, INF);
  dist[source] = 0;
  for(int i=0; i<n; i++) {
    bool update = false;
    for(auto e : edges) {
      if(dist[e.from] != INF && dist[e.to] > dist[e.from] + e.dist) {
        if(i==n-1) { return vector<long long>(0); /* negative cycle detected */ }
        dist[e.to] = dist[e.from] + e.dist;
        update = true;
      }
    }
    if (!update) break;
  }
  return dist;
}

const long long INF = numeric_limits<long long>::max()/2;
struct edge {int to; int dist;};
vector<long long> dijkstra(int source, vector<vector<edge>> const &adjlist) {
  /* O( (|E|+|V|) * log|V| ) */
  vector<long long> dist(adjlist.size(), INF);
  priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> q;
  dist[source] = 0;
  q.emplace(0, source);
  while(q.size()) {
    auto [d, v] = q.top(); q.pop();
    if(dist[v] < d) continue;
    for(auto e : adjlist[v]) if(dist[e.to] > dist[v] + e.dist) {
      dist[e.to] = dist[v] + e.dist;
      q.emplace(dist[e.to], e.to);
    }
  }
  return dist;
}

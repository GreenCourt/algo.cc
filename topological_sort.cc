vector<int> topological_sort(const vector<vector<int>> &adjlist) {
  /* O(|V| + |E|) */
  int n = ssize(adjlist);
  vector<int> degree_in(n);
  for(int i=0; i<n; ++i) for(int u:adjlist[i]) degree_in[u]++;
  vector<int> seq;
  queue<int> q; // use priority_queue if you need a lexicographically smallest sequence in O(|V| log |V| + |E|)
  for(int i=0; i<n; ++i) if(degree_in[i] == 0) q.push(i);
  while(q.size()) {
    int v = q.front(); q.pop();
    seq.push_back(v);
    for(int u: adjlist[v]) if(--degree_in[u] == 0) q.push(u);
  }
  if(ssize(seq) != n) return vector<int>(); // not a DAG
  return seq;
}

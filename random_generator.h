mt19937_64 rnd = mt19937_64(random_device()());

template<typename T>
inline T randint(T mn, T mx) { // [mn, mx]
  return uniform_int_distribution<T>(mn, mx)(rnd);
}

template<typename T>
vector<T> random_vector(int n, T mn, T mx) { // [mn, mx]
  /* O(n) */
  assert(mn <= mx);
  uniform_int_distribution<T> dist(mn, mx);
  vector<T> a(n);
  for(int i=0; i<n; ++i) a[i] = dist(rnd);
  return a;
}

template<typename T>
vector<T> random_vector_without_duplicates(int n, T mn, T mx) { // [mn, mx]
  /* O(n) */ // Fisher-Yates
  assert(mn <= mx);
  vector<T> a(n);
  unordered_map<T,T> m;
  T r = mx - mn;
  for(int i=0; i<n; ++i,--r) {
    T k = randint(T(0), r);
    a[i] = (m.count(k) ? m[k] : k) + mn;
    m[k] = (m.count(r) ? m[r] : r);
  }
  return a;
}

template<typename T>
vector<T> random_permutation(T mn, T mx) { // [mn, mx]
  /* O(n) */
  assert(mn <= mx);
  vector<T> a(mx - mn + 1);
  iota(a.begin(),a.end(),mn);
  shuffle(a.begin(), a.end(), rnd);
  return a;
}

template<typename T>
pair<T,T> random_pair(T mn, T mx, bool allow_same) { // [mn, mx]
  /* O(1) */
  assert(mn <= mx);
  T a = randint(mn, mx), b;
  if(allow_same) {
    b = randint(mn, mx);
  }
  else {
    assert(mn != mx);
    b = randint(mn, mx-1);
    if(a == b) b = mx;
  }
  return {a, b};
}

template<typename T>
pair<T,T> random_range(T mn, T mx, bool allow_same) { // [mn, mx]
  /* O(1) */
  assert(mn <= mx);
  T l,r;
  if(allow_same) {
    l = randint(mn, mx);
    r = randint(l, mx);
  }
  else {
    assert(mn != mx);
    l = randint(mn, mx-1);
    r = randint(l+1, mx);
  }
  return {l, r};
}

vector<pair<int,int>> random_graph(int n, int m) {
  /* O(n^2) */
  assert(m <= n*(n-1)/2);
  vector<pair<int,int>> edges; // 0-indexed edge list
  edges.reserve(m);
  int r = (n*(n-1) / 2) - 1;
  for(int a=0; a<n; ++a) for(int b=a+1; b<n; ++b)
    if(randint(0, r--) < m - edges.size()) edges.emplace_back(a,b);
  assert(edges.size() == m);
  return edges;
}

vector<pair<int,int>> random_path_graph(int n) {
  /* O(n) */
  vector<pair<int,int>> edges(n-1); // 0-indexed edge list
  vector<int> p = random_permutation(0, n-1);
  for(int i=0; i<n-1; ++i) edges[i] = {p[i], p[i+1]};
  return edges;
}

vector<pair<int,int>> random_star_graph(int n) {
  /* O(n) */
  vector<pair<int,int>> edges; // 0-indexed edge list
  edges.reserve(n-1);
  int center = randint(0, n-1);
  for(int i=0; i<n; ++i) if(i!=center) edges.emplace_back(center,i);
  return edges;
}

vector<pair<int,int>> random_tree(int n) {
  /* O(n log n) */
  if(n==1) return {};
  vector<pair<int,int>> edges; // 0-indexed edge list
  edges.reserve(n-1);
  vector<int> prufer_sequence(n-2);
  for(int i=0; i<n-2; ++i) prufer_sequence[i] = randint(0, n-1);
  vector<int> count(n, 1);
  for(int v : prufer_sequence) count[v]++;
  priority_queue<int, vector<int>, greater<int>> q;
  for(int v=0; v<n; ++v) if(count[v]==1) q.push(v);
  while(prufer_sequence.size()) {
    int v= q.top(); q.pop();
    int u = prufer_sequence.back(); prufer_sequence.pop_back();
    edges.emplace_back(u,v);
    count[u]--, count[v]--;
    if(count[u] == 1) q.push(u);
  }
  vector<int> nonzero;
  for(int v=0; v<n; ++v) if(count[v]) nonzero.push_back(v);
  assert(nonzero.size() == 2);
  edges.emplace_back(nonzero[0], nonzero[1]);
  assert(edges.size() == n-1);
  return edges;
}

vector<pair<int,int>> random_connected_graph(int n, int m) {
  /* O(n^2) */
  assert(m <= n*(n-1)/2);
  assert(m >= n-1);
  vector<pair<int,int>> edges = random_tree(n); // 0-indexed edge list
  edges.reserve(m);

  vector<vector<bool>> check(n, vector<bool>(n, false));
  for(int i=0; i<n-1; ++i) {
    int u = edges[i].first, v = edges[i].second;
    check[u][v] = check[v][u] = true;
  }

  int required = m - edges.size();
  int candidates = (n*(n-1) / 2)  - edges.size();
  int r = candidates - 1;
  for(int a=0; a<n; ++a) for(int b=a+1; b<n; ++b) if(!check[a][b]) 
    if(randint(0, r--) < required) edges.emplace_back(a,b), required--;
  assert(edges.size() == m);
  return edges;
}

const string string_digits = "0123456789";
const string string_alphabet_lowercase = "abcdefghijklmnopqrstuvwxyz";
const string string_alphabet_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string random_string(int n, const string &population = string_digits + string_alphabet_lowercase + string_alphabet_uppercase) {
  /* O(n) */
  string r; r.reserve(n);
  int sz = population.size();
  for(int i=0; i<n; ++i) r.push_back(population[randint(0, sz-1)]);
  return r;
}

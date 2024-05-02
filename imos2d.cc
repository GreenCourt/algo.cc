template<typename T=long long, typename S>
vector<vector<T>> Imos2D(
    int x_max, int y_max,
    vector<int> const &x_begin, // half-open
    vector<int> const &y_begin, // x_begin <= x < x_end
    vector<int> const &x_end,   // y_begin <= y < y_end
    vector<int> const &y_end,
    vector<S> const &val
    ) {
  /* O(x_max*y_max + A.size()) */
  vector d(x_max+1, vector<T>(y_max+1));
  int sz = ssize(val);
  assert(sz == ssize(x_begin) && sz == ssize(x_end));
  assert(sz == ssize(y_begin) && sz == ssize(y_end));
  for(int i=0; i<sz; ++i) {
    assert(0 <= x_begin[i] && x_begin[i] <= x_end[i] && x_end[i] <= x_max+1);
    assert(0 <= y_begin[i] && y_begin[i] <= y_end[i] && y_end[i] <= y_max+1);
    d[x_begin[i]][y_begin[i]] += val[i];
    if(y_end[i] <= y_max) d[x_begin[i]][y_end[i]] -= val[i];
    if(x_end[i] <= x_max) d[x_end[i]][y_begin[i]] -= val[i];
    if(y_end[i] <= y_max && x_end[i] <= x_max) d[x_end[i]][y_end[i]] += val[i];
  }
  for(int x=0; x<=x_max; ++x) for(int y=1; y<=y_max; ++y) d[x][y] += d[x][y-1];
  for(int y=0; y<=y_max; ++y) for(int x=1; x<=x_max; ++x) d[x][y] += d[x-1][y];
  return d;  // d[x][y]
}

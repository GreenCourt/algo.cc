using area = tuple<int,int,int,int>; /* x_begin, y_begin, x_end, y_end
                                        (half-open)
                                        x_begin <= x < x_end
                                        y_begin <= y < y_end */
vector<vector<int>> Imos2D(int x_max, int y_max, vector<area> const &A) {
  /* O(x_max*y_max + A.size()) */
  vector d(x_max+1, vector<int>(y_max+1));
  for(auto [x_begin, y_begin, x_end, y_end] : A) {
    assert(0 <= x_begin && x_begin <= x_end && x_end <= x_max+1);
    assert(0 <= y_begin && y_begin <= y_end && y_end <= y_max+1);
    d[x_begin][y_begin]++;
    if(y_end <= y_max) d[x_begin][y_end]--;
    if(x_end <= x_max) d[x_end][y_begin]--;
    if(y_end <= y_max && x_end <= x_max) d[x_end][y_end]++;
  }
  for(int x=0; x<=x_max; ++x) for(int y=1; y<=y_max; ++y) d[x][y] += d[x][y-1];
  for(int y=0; y<=y_max; ++y) for(int x=1; x<=x_max; ++x) d[x][y] += d[x-1][y];
  return d;  // d[x][y]
}

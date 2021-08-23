using area = tuple<int,int,int,int>; /* x_start, y_start, x_last, y_last
                                        (all inclusive)
                                        x_start <= x <= x_last
                                        y_start <= y <= y_last */
vector<vector<int>> Imos2D(int x_max, int y_max, vector<area> const &A) {
  /* O(x_max*y_max + A.size()) */
  vector d(x_max+1, vector<int>(y_max+1));
  for(auto [x_start, y_start, x_last, y_last] : A) {
    assert(0<=x_start && x_start <= x_last && x_last <=x_max);
    assert(0<=y_start && y_start <= y_last && y_last <=y_max);
    d[x_start][y_start]++;
    d[x_start][y_last]--;
    d[x_last][y_start]--;
    d[x_last][y_last]++;
  }
  for(int x=0; x<=x_max; ++x) for(int y=1; y<=y_max; ++y) d[x][y] += d[x][y-1];
  for(int y=0; y<=y_max; ++y) for(int x=1; x<=x_max; ++x) d[x][y] += d[x-1][y];
  return d; // d[x][y]
}

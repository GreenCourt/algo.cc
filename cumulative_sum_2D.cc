template<typename T=long long>
struct CumulativeSum2D {
  vector<vector<T>> csum;
  CumulativeSum2D() {}
  template<typename S>
  CumulativeSum2D(vector<vector<S>> const &input) : csum(input.size() + 1, vector<T>(input[0].size() + 1, 0)) {
    for(int i = 0; i < (int)input.size(); i++) for(int j = 0; j < (int)input[i].size(); j++)
      csum[i+1][j+1] += csum[i+1][j] + csum[i][j+1] - csum[i][j] + input[i][j];
  }
  CumulativeSum2D(vector<string> const &input, char target) : csum(input.size() + 1, vector<T>(input[0].size() + 1, 0)) {
    for(int i = 0; i < (int)input.size(); i++) for(int j = 0; j < (int)input[i].size(); j++)
      csum[i+1][j+1] += csum[i+1][j] + csum[i][j+1] - csum[i][j] + (input[i][j]==target);
  }
  T query(int y_top, int x_left, int y_bottom, int x_right) { /* [x_left, x_right), [y_top, y_bottom) */
    return csum[y_bottom][x_right] - csum[y_top][x_right] - csum[y_bottom][x_left] + csum[y_top][x_left];
  }
};

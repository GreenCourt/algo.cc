vector<vector<int>> bfs(const vector<string>& grid, int start_r, int start_c, char wall = '#', bool allow_diagonal = false) {
  /* O(rows * cols) */
  int rows = grid.size(), cols = grid[0].size();
  auto direction = allow_diagonal
    ? vector<pair<int,int>>({{0,-1}, {-1,0}, {1,0}, {0,1}, {-1,-1}, {-1,1}, {1,-1}, {1,1}})
    : vector<pair<int,int>>({{0,-1}, {-1,0}, {1,0}, {0,1}});

  vector<vector<int>> dist(rows, vector<int>(cols, -1));
  queue<pair<int,int>> q;
  dist[start_r][start_c] = 0;
  q.emplace(start_r, start_c);
  while(q.size()) {
    auto [r, c] = q.front(); q.pop();
    int d = dist[r][c];
    for(auto [dr, dc] : direction) {
      int rr = r+dr, cc = c+dc;
      if( rr < 0 || rr >= rows || cc < 0 || cc >= cols) continue;
      if( grid[rr][cc] == wall) continue;
      if( dist[rr][cc] != -1) continue;  // already visited
      dist[rr][cc] = d + 1;
      q.emplace(rr,cc);
    }
  }
  return dist;
}

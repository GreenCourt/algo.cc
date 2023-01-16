const double EPS=1e-5;
using Vector = vector<double>;
using Matrix = vector<Vector>;

int gauss_jordan(Matrix& A, bool is_extended = false) {
  /* O(rows * cols^2) */
  int m = A.size(), n = A[0].size(); // m rows, n columns
  int rank = 0;
  for (int col = 0; col < n; ++col) {
    if (is_extended && col == n-1) break;
    int pivot = -1; auto mx = EPS;
    for (int row = rank; row < m; ++row) if (abs(A[row][col]) > mx) {
      mx = abs(A[row][col]); pivot = row;
    }
    if (pivot == -1) continue;
    swap(A[pivot], A[rank]);
    {
      auto fac = A[rank][col];
      for (int col2 = 0; col2 < n; ++col2) A[rank][col2] /= fac;
    }
    for (int row = 0; row < m; ++row) if (row != rank && abs(A[row][col]) > EPS) {
      auto fac = A[row][col];
      for (int col2 = 0; col2 < n; ++col2) A[row][col2] -= A[rank][col2] * fac;
    }
    ++rank;
  }
  return rank;
}

Vector linear_equations(Matrix& A, Vector& b) {
  /* O(rows * cols^2) */
  int m = A.size(), n = A[0].size(); // m rows, n cols
  assert(b.size() == m);
  Matrix ex(m, Vector(n+1));
  for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) ex[i][j] = A[i][j];
  for(int i=0; i<m; ++i) ex[i][n] = b[i];
  int rank = gauss_jordan(ex, true);
  for (int row = rank; row < m; ++row) if (abs(ex[row][n]) > EPS) return Vector(0);
  Vector r(n);
  for(int i=0; i<n; ++i) r[i] = ex[i][n];
  return r;
}

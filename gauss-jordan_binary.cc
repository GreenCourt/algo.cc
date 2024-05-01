using BitRow=bitset<1000>;
struct BitMatrix {
  int rows, cols; vector<BitRow> matrix;
  BitMatrix(int rows_ = 1, int cols_ = 1) : rows(rows_), cols(cols_), matrix(vector<BitRow>(rows_)) {}
  inline BitRow& operator [] (int i) {return matrix[i];}
};

int gauss_jordan(BitMatrix &A, bool is_extended = false) {
  /* O(rows * cols^2) */
  int rank = 0;
  for (int col = 0; col < A.cols; ++col) {
    if (is_extended && col == A.cols - 1) break;
    int pivot = -1;
    for (int row = rank; row < A.rows; ++row) if (A[row][col]) {
      pivot = row; break;
    }
    if (pivot == -1) continue;
    swap(A[pivot], A[rank]);
    for (int row = 0; row < A.rows; ++row) if (row != rank && A[row][col]) A[row] ^= A[rank];
    ++rank;
  }
  return rank;
}

pair<int, vector<int>> linear_equations(BitMatrix A, vector<int> b) {
  /* O(rows * cols^2) */
  int m = A.rows, n = A.cols;
  BitMatrix ex(m, n + 1);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) ex[i][j] = A[i][j];
    ex[i][n] = b[i];
  }
  int rank = gauss_jordan(ex, true);
  for (int row = rank; row < m; ++row) if (ex[row][n]) return {-1, vector<int>(0)}; // no solution
  vector<int> sol(n, 0);
  for (int i = 0; i < rank; ++i) sol[i] = ex[i][n];
  return {rank, sol};
}

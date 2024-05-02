using Vector = vector<long long>;
using Matrix = vector<Vector>;

int modinv(long long a, int mod) {
  /* O(log mod) */
  assert(a>=0);
  assert(gcd(a,mod)==1);
  long long b = mod, u = 1, v = 0;
  while (b) {
    long long t = a / b;
    a -= t * b; swap(a, b);
    u -= t * v; swap(u, v);
  }
  u %= mod;
  if (u < 0) u += mod;
  return (int)u;
}

int gauss_jordan(Matrix& A, int mod, bool is_extended = false) {
  /* O(rows * cols^2) */
  int m = ssize(A), n = ssize(A[0]); // m rows, n columns
  for(int row = 0; row < m; ++row) for (int col = 0; col < n; ++col)
    A[row][col] = (A[row][col] % mod + mod) % mod;
  int rank = 0;
  for(int col = 0; col < n; ++col) {
    if(is_extended && col == n-1) break;
    int pivot = -1;
    for(int row = rank; row < m; ++row) if (A[row][col]) {
      pivot = row; break;
    }
    if(pivot == -1) continue;
    swap(A[pivot], A[rank]);
    long long inv = modinv(A[rank][col], mod);
    for(int col2 = 0; col2 < n; ++col2) A[rank][col2] = A[rank][col2] * inv % mod;
    for(int row = 0; row < m; ++row) if (row != rank && A[row][col]) {
      long long fac = A[row][col];
      for(int col2 = 0; col2 < n; ++col2) {
        A[row][col2] -= A[rank][col2] * fac % mod;
        if (A[row][col2] < 0) A[row][col2] += mod;
      }
    }
    ++rank;
  }
  return rank;
}

pair<int, Vector> linear_equations(Matrix& A, Vector& b, int mod) {
  /* O(rows * cols^2) */
  int m = ssize(A), n = ssize(A[0]); // m rows, n cols
  assert(ssize(b) == m);
  Matrix ex(m, Vector(n+1));
  for(int i=0; i<m; ++i) for(int j=0; j<n; ++j) ex[i][j] = A[i][j];
  for(int i=0; i<m; ++i) ex[i][n] = b[i];
  int rank = gauss_jordan(ex, mod, true);
  for (int row = rank; row < m; ++row) if(ex[row][n]) return {-1,Vector(0)}; // no solution
  Vector sol(n);
  for(int i=0; i<n; ++i) sol[i] = ex[i][n];
  return {rank,sol};
}

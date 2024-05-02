using Vector = vector<long long>;
using Matrix = vector<Vector>;

Matrix matmul(const Matrix &A, const Matrix &B, int mod=0) {
  assert(A[0].size() == B.size());
  int n = ssize(A), m = ssize(A[0]), l = ssize(B[0]);
  Matrix C(n, Vector(l));
  for(int i=0; i<m; i++) for(int j=0; j<n; j++) for(int k=0; k<l; k++) {
    if(mod) C[j][k] = (C[j][k] + ((A[j][i]%mod) * (B[i][k]%mod) % mod)) % mod;
    else C[j][k] += A[j][i] * B[i][k];
  }
  return C;
}

Vector matmul(const Matrix &A, const Vector &b, int mod=0) {
  assert(A[0].size() == b.size());
  int n = ssize(A), m = ssize(A[0]);
  Vector C(n);
  for(int i=0; i<m; i++) for(int j=0; j<n; j++) {
    if(mod) C[j] = (C[j] + (((A[j][i]%mod) * (b[i]%mod))%mod)) % mod;
    else C[j] += A[j][i] * b[i];
  }
  return C;
}

Matrix matpow(const Matrix &A, long long p, int mod=0) {
  assert(A.size() == A[0].size());
  int n = ssize(A);
  Matrix B(n, Vector(n));
  for(int i=0; i<n; i++) B[i][i] = 1;
  Matrix C(A);
  while (p > 0) {
    if (p & 1) {B = matmul(B, C, mod);}
    C = matmul(C, C, mod);
    p >>= 1;
  }
  return B;
}

Matrix identity_matrix(int n) {
  Matrix mat(n, Vector(n, 0));
  for(int i=0; i< n; i++) mat[i][i] = 1;
  return mat;
}

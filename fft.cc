void fft(vector<complex<double>> &seq /* will be modified */, bool inverse = false) {
  /* O(n log n) */
  int n = ssize(seq);
  int ln = 0; // log2(n)
  while(1<<ln < n) ln++;
  assert(n == 1<<ln);
  for(int i=0; i<n; i++) {
    int j = 0;
    for(int k=0; k<ln; k++) j |= (i >> k & 1) << (ln - 1 - k);
    if(i<j) swap(seq[i], seq[j]);
  }
  constexpr double tau = 2 * numbers::pi;
  double t = tau / n * (inverse ? 1 : -1);
  complex<double> zeta = complex<double>(cos(t), sin(t));
  vector<complex<double>> zeta_pow(n, 1);
  for(int i=1; i<n; ++i) zeta_pow[i] = zeta_pow[i-1] * zeta;
  for(int b=1; b<n; b <<= 1) {
    for(int j = 0; j < b; j++) {
      for(int k = 0; k < n; k += b * 2) {
        int l=j+k, r=j+k+b;
        complex<double> sl = seq[l], sr = seq[r] * zeta_pow[n / (2*b) * j];
        seq[l] = sl + sr, seq[r] = sl - sr;
      }
    }
  }
  if(inverse) for(int i=0; i<n; i++) seq[i] /= n;
}

vector<complex<double>> fft(const vector<double> &input, bool inverse=false) {
  /* O(n log n) */
  int n = ssize(input);
  vector<complex<double>> c(n);
  for(int i=0; i<n; ++i) c[i] = complex<double>(input[i], 0);
  fft(c, inverse);
  return c;
}

template<typename T>
vector<T> convolution(const vector<T> &a, const vector<T> &b) {
  /* O(n log n) */
  assert(a.size() && b.size());
  int n = ssize(a) + ssize(b) - 1;
  int p2 = 1;
  while(p2 < n) p2 <<= 1;
  vector<complex<double>> A(p2), B(p2);
  for(int i=0; i<ssize(a); ++i) A[i] = complex<double>(a[i], 0);
  for(int i=0; i<ssize(b); ++i) B[i] = complex<double>(b[i], 0);
  fft(A), fft(B);
  for(int i=0; i<p2; i++) A[i] *= B[i];
  fft(A, true);
  vector<T> c(n);
  for(int i=0; i<n; i++) {
    if constexpr (is_floating_point<T>::value) c[i] = (T)A[i].real();
    else c[i] = (T)round(A[i].real());
  }
  return c;
}

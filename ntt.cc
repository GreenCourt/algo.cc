void ntt(vector<Modint<998244353>> &seq /* will be modified */, bool inverse = false) {
  /* O(n log n) */
  int n = seq.size();
  int ln = 0; // log2(n)
  while(1<<ln < n) ln++;
  assert(n == 1<<ln);
  assert(ln <= 23);
  auto zeta = Modint<998244353>(3).pow(119);
  for(int i=0; i<23-ln; ++i) zeta *= zeta;
  if(!inverse) zeta = zeta.inv();
  vector<Modint<998244353>> zeta_pow(n, 1);
  for(int i=1; i<n; ++i) zeta_pow[i] = zeta_pow[i-1] * zeta;
  for(int i=0; i<n; i++) {
    int j = 0;
    for(int k=0; k<ln; k++) j |= (i >> k & 1) << (ln - 1 - k);
    if(i<j) swap(seq[i], seq[j]);
  }
  for(int b=1; b<n; b <<= 1) {
    for(int j = 0; j < b; j++) {
      for(int k = 0; k < n; k += b * 2) {
        int l=j+k, r=j+k+b;
        auto sl = seq[l], sr = seq[r] * zeta_pow[n / (2*b) * j];
        seq[l] = sl + sr, seq[r] = sl - sr;
      }
    }
  }
  auto ninv = Modint<998244353>(n).inv();
  if(inverse) for(int i=0; i<n; i++) seq[i] *= ninv;
}

vector<Modint<998244353>> convolution(vector<Modint<998244353>> a, vector<Modint<998244353>> b) {
  /* O(n log n) */
  assert(a.size() && b.size());
  int n = a.size() + b.size() - 1;
  int p2 = 1;
  while(p2 < n) p2 <<= 1;
  a.resize(p2); b.resize(p2);
  ntt(a), ntt(b);
  for(int i=0; i<p2; i++) a[i] *= b[i];
  ntt(a, true);
  a.resize(n);
  return a;
}

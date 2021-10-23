struct sieve {
  int n;
  vector<int> f, primes;
  sieve(int n=1) : n(n), f(n+1, 0) {
    /* O(n log log n) */
    f[0] = f[1] = -1;
    for(int i=2; i<=n; i++) {
      if(f[i]) continue;
      primes.push_back(i); f[i] = i;
      for(long long k=(long long)i*i; k<=n; k+=i) if(!f[k]) f[k] = i;
    }
  }
  bool is_prime(int x) {return f[x]==x;}
  template <typename T>
  vector<pair<T,int>> factors(T x) {
    /* O(log x) */
    assert(x <= n);
    vector<pair<T,int>> fc;
    while (x != 1) {
      if (fc.size() && fc.back().first == f[x]) fc.back().second++;
      else fc.emplace_back(f[x], 1);
      x /= f[x];
    }
    return fc;
  }
};

vector<int> number_of_prime_factors(int n) {
  /* O(n log log n) */
  vector<int> r(n+1, 1); r[0] = 0;
  for(int i=2; i<=n; i++) {
    if(r[i]>1) continue;
    for(int k=2; i*k <= n; k++) r[i*k] = r[i] + r[k];
  }
  return r;
}

vector<int> number_of_unique_prime_factors(int n) {
  /* O(n log log n) */
  vector<int> r(n+1, 0); r[1] = 1;
  for(int i=2; i<=n; i++) {
    if(r[i]) continue;
    for(int k=i; k <= n; k+=i) r[k] += 1;
  }
  return r;
}

template <typename T>
bool is_prime(T n){
  /* O(sqrt n) */
  if(n<=1) return false;
  for(T i=2;i*i<=n;i++) if(n%i==0) return false;
  return true;
}

template <typename T>
vector<pair<T,int>> prime_factors(T n){
  /* O(sqrt n) */
  vector<pair<T,int>> fc;
  T x = n;
  for(T i=2;i*i<=n;i++) {
    int c=0;
    while (x%i == 0) x /= i, ++c;
    if(c) fc.emplace_back(i,c);
  }
  if(x!=1) fc.emplace_back(x,1);
  return fc;
}

long long euler_phi(long long n) {
  /* O(sqrt n) */
  long long phi = n;
  for(auto [f,c] : prime_factors(n)) phi = phi / f * (f-1);
  return phi;
}

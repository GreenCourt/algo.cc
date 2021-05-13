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
    assert((long long)n*n >= x);
    vector<pair<T,int>> fc;
    if( x<=n ) {
      /* O(log x) */
      while (x != 1) {
        if (fc.size() && fc.back().first == f[x]) fc.back().second++;
        else fc.emplace_back(f[x], 1);
        x /= f[x];
      }
    }
    else{
      /* O(sqrt(x)) */
      for (int p : primes) {
        int c = 0;
        while (x%p == 0) x /= p, ++c;
        if (c != 0) fc.emplace_back(p,c);
      }
      if(x!=1) fc.emplace_back(x,1);
    }
    return fc;
  }
};

bool is_prime(int n){
  /* O(sqrt n) */
  if(n<=1) return false;
  for(int i=2;i*i<=n;i++) if(n%i==0) return false;
  return true;
}

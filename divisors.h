vector<long long> divisors(long long n) {
  /* O(sqrt(n)) */
  vector<long long> d1,d2;
  for(long long i = 1; i * i <= n; i++) if(n % i == 0) {
    d1.push_back(i);
    if(i * i != n) d2.push_back(n / i);
  }
  for(auto it=d2.rbegin(); it!=d2.rend(); ++it) d1.push_back(*it);
  return d1;
}

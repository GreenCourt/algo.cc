tuple<long long, long long, long long> ext_gcd(long long a, long long b) {
  if (b == 0) return {a, 1, 0};
  auto [gcd, y, x] = ext_gcd(b, a%b);
  y -= a/b * x;
  return {gcd, x, y}; // a*x + b*y = gcd
}

pair<long long,long long> crt(const vector<long long> &r, const vector<long long> &m) {
  // return x that satisfies x = a mod b, for a in r, for b in m
  // O(n log lcm(m[i]))
  assert(r.size() == m.size());
  auto mod=[&](long long a,long long k){return (a%k+k)%k;}; // a mod k for negative a
  long long r_ = 0, lcm = 1; int n = r.size();
  for(int i=0; i<n; ++i) {
    long long ri = mod(r[i],m[i]), mi = m[i];
    assert(mi > 0);
    if(mi > lcm) swap(mi,lcm), swap(ri,r_);
    auto [g, p, q] = ext_gcd(lcm, mi);
    if((ri-r_) % g) return make_pair(0,0); // no solution exists
    r_ += lcm * ((ri-r_)/g % (mi/g) * p % (mi/g));
    lcm *= mi/g;
    if(r_<0) r_+= lcm;
  }
  return make_pair(r_, lcm); // x = r_ mod lcm
}
template<typename T=long long, typename S>
vector<T> Imos(int mx, vector<int> const &left, vector<int> const &right, vector<S> const &val) {
  /* O(mx + val.size()) */
  assert(val.size() == left.size());
  assert(val.size() == right.size());
  int sz = ssize(val);
  vector<T> d(mx+1);
  for(int i=0; i<sz; ++i) {
    assert(0<=left[i] && left[i] < right[i] && right[i] <=mx+1); /* [l,r) */
    d[left[i]] += val[i];
    if(right[i] <= mx) d[right[i]] -= val[i];
  }
  for(int i=1; i<=mx; ++i) d[i] += d[i-1];
  return d;
}

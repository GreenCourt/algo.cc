template<typename T>
long long inversion_number(const vector<T> &a, T mn, T mx) {
  /* O(n log n) */
  int n = ssize(a);
  T sz = mx - mn + 1;
  assert(mn <= mx);
  fenwick_tree<long long> ft(sz);
  long long x = 0;
  for(int i=0; i<n; ++i) {
    assert(mn <= a[i] && a[i] <= mx);
    ft.add(a[i]-mn, 1);
    x += ft.sum(a[i]-mn+1, sz);
  }
  return x;
}

template<typename T>
long long inversion_number(const vector<T> &a) {
  /* O(n log n) */
  int n = ssize(a);
   /* coordinate compression */
  vector<T> b(a);
  vector<int> c(n);
  sort(b.begin(), b.end());
  b.erase(unique(b.begin(), b.end()), b.end());
  for(int i=0; i<n; ++i) c[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
  return inversion_number<int>(c, 0, ssize(b)-1);
}

template<class F>
long long ternary_search(long long low, long long high, F f) {
  /* O(iteration * O(f)) */
  /* Find the value that minimizes f. */
  while (high-low > 2) {
    long long m1 = low + (high-low) / 3;
    long long m2 = high - (high-low) / 3;
    if (f(m1) < f(m2)) high = m2;
    else low = m1;
  }
  return min({make_pair(f(low),low), make_pair(f(low+1),low+1), make_pair(f(low+2),low+1)}).second;
}

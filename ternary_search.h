double ternary_search(double low, double high, int iteration, function<double(double)> f) {
  /* O(iteration * O(f)) */
  /* Find the value that minimizes f. */
  while (iteration--) {
    double m1 = (low * 2 + high) / 3;
    double m2 = (low + high * 2) / 3;
    if (f(m1) < f(m2)) high = m2;
    else low = m1;
  }
  return low;
}

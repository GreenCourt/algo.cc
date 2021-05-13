double BinarySearch(double l, double r, int iteration, function<bool(double)> f) {
  /* O(iteration * O(f)) */
  /* [l,r] both inclusive */
  /* Find the boundary T and F that satisfies (f(T)==true && f(F)==false) for (iteration) times. */
  bool fl = f(l), fr = f(r); assert(fl!=fr);
  double &T = fl ? l : r, &F = fr ? l : r;
  while(iteration--) {
    double m = l + (r-l) / 2;
    if(f(m)) T = m;
    else F = m;
  }
  return T;
}

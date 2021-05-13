long long BinarySearch(long long l, long long r, function<bool(long long)> f) {
  /* O(log(r-l) * O(f)) */
  /* [l,r] both inclusive */
  /* Find the boundary T and F that satisfies (f(T)==true && f(F)==false && abs(T-F)==1). */
  bool fl = f(l), fr = f(r); assert(fl!=fr);
  long long &T = fl ? l : r, &F = fr ? l : r;
  while(r-l>1) {
    long long m = l + (r-l) / 2;
    if(f(m)) T = m;
    else F = m;
  }
  return T;
}

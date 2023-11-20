template<bool strict=true, typename T>
vector<T> longest_increasing_subsequence(vector<T> const &seq) {
  /* O(n log n) */
  /* return one of the longest increasing subsequence */
  vector<T> lis;
  for(T x:seq){
    auto b = strict
      ? lower_bound(lis.begin(), lis.end(), x)
      : upper_bound(lis.begin(), lis.end(), x);
    if(b!=lis.end()) *b = x;
    else lis.push_back(x);
  }
  return lis;
}

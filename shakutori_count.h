template<typename T>
long long shakutori_count(vector<T> const &input, long long upper_limit) {
  /* O(n) */
  /* returns the number of sequences whose sum <= upper_limit. */
  int r = 0, n = input.size();
  long long sum = 0, count = 0;
  for(int l=0; l<n; ++l) { // consider [l,r)
    while(r<n && (sum + input[r] <= upper_limit)) sum += input[r++];
    count += r - l;
    sum -= input[l];
  }
  return count;
}

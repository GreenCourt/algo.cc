template<typename T>
int shakutori_minimum_length(vector<T> const &input, long long lower_limit) {
  /* O(n) */
  /* returns the minimum length of sequence whose sum >= lower_limit. */
  int r = 0, n = input.size(), minimum_length = n + 1;
  long long sum = 0;
  for(int l=0; l<n; ++l) { // consider [l,r)
    while(r<n && (sum  < lower_limit)) sum += input[r++];
    if(sum >= lower_limit) minimum_length = min(minimum_length, r - l);
    sum -= input[l];
  }
  return minimum_length;
}

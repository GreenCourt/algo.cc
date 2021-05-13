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

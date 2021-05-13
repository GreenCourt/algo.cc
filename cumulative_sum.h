struct CumulativeSum {
  vector<long long> csum;
  CumulativeSum() {}
  template<typename T>
  CumulativeSum(vector<T> const &input) : csum(input.size() + 1, 0) {
    for(int i = 0; i < (int)input.size(); i++) csum[i+1] = csum[i] + input[i];
  }
  long long query(int l, int r) { /* [l,r) */ return csum[r] - csum[l]; }
};

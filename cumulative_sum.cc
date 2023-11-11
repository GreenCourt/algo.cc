template<typename T=long long>
struct CumulativeSum {
  vector<T> csum;
  CumulativeSum() {}
  template<typename S>
  CumulativeSum(vector<S> const &input) : csum(input.size() + 1, 0) {
    for(int i = 0; i < (int)input.size(); i++) csum[i+1] = csum[i] + input[i];
  }
  T query(int l, int r) { /* [l,r) */ assert(l<=r); return csum[r] - csum[l]; }
};

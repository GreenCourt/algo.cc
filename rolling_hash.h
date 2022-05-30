template<typename T>
vector<int> find_all_matches_by_rolling_hash(const T& text, const T& pattern, unsigned long long b=1000000007) {
  /* O(n + m) */
  int n = pattern.size();
  int m = text.size();
  assert(n > 0);
  assert(m > 0);
  if(n > m) return vector<int>();

  /* For unsigned long long, overflow is same as mod 2^64 */
  unsigned long long B = 1;
  for(int i=0; i<n-1; ++i) B *= b;

  unsigned long long hash_p = 0, hash_t= 0;
  for(int i=0; i<n; ++i) {
    hash_p = b * hash_p + pattern[i];
    hash_t = b * hash_t + text[i];
  }

  vector<int> index;
  if(hash_p == hash_t) index.push_back(0);
  for(int i=n; i<m; i++) {
    hash_t = (b * (hash_t - B * text[i-n]) + text[i]);
    if(hash_p == hash_t) index.push_back(i-n+1);
  }
  return index;
}

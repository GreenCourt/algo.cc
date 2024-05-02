template<typename T>
int interval_scheduling(const vector<pair<T,T>> &RL, bool half_open=false) {
  /* O(n log n) */
  int n = ssize(RL);
  if(n==0) return 0;
  vector rl(RL);
  sort(rl.begin(), rl.end()); 
  int ans = 1;
  T b = rl[0].first;
  for(int i=1; i<n; ++i)
    if(half_open ? (rl[i].second >= b) : (rl[i].second > b))
      ans++, b=rl[i].first;
  return ans;
}

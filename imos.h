vector<int> Imos(int mx, vector<pair<int,int>> const &area) {
  /* O(mx + area.size()) */
  vector<int> d(mx+2), sum(mx+1);
  for(auto [l,r] : area) {
    assert(0<=l && l < r && r <=mx+1); /* [l,r) */
    d[l]++, d[r]--;
  }
  sum[0] = d[0];
  for(int i=1; i<=mx; ++i) sum[i] = sum[i-1] + d[i];
  return sum;
}

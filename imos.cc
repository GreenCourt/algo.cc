vector<int> Imos(int mx, vector<pair<int,int>> const &area) {
  /* O(mx + area.size()) */
  vector<int> d(mx+1);
  for(auto [l,r] : area) {
    assert(0<=l && l < r && r <=mx+1); /* [l,r) */
    d[l]++;
    if(r <= mx) d[r]--;
  }
  for(int i=1; i<=mx; ++i) d[i] += d[i-1];
  return d;
}

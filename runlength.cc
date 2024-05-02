vector<pair<char, int>> runlength(const string& s) {
  vector<pair<char,int>> r;
  int n=ssize(s), len=1;
  for(int i=1; i<n; ++i) {
    if(s[i] == s[i-1]) len++;
    else { r.emplace_back(s[i-1], len); len=1; }
  }
  r.emplace_back(s.back(), len);
  return r;
}

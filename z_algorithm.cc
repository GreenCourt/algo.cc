vector<int> z_algorithm(const string &s) {
  // O(n)
  vector<int> z(s.size());
  z[0]=s.size();
  int i=1, j=0;
  while(i<s.size()) {
    while(i+j < s.size() && s[j]==s[i+j]) ++j;
    z[i]=j;
    if(j==0) {++i; continue;}
    int k=1;
    while(i+k < s.size() && k+z[k] < j) z[i+k]=z[k], ++k;
    i+=k, j-=k;
  }
  return z;
}

vector<int> z_algorithm(const string &s) {
  // O(n)
  vector<int> z(s.size());
  z[0]=ssize(s);
  int i=1, j=0;
  while(i<ssize(s)) {
    while(i+j < ssize(s) && s[j]==s[i+j]) ++j;
    z[i]=j;
    if(j==0) {++i; continue;}
    int k=1;
    while(i+k < ssize(s) && k+z[k] < j) z[i+k]=z[k], ++k;
    i+=k, j-=k;
  }
  return z;
}

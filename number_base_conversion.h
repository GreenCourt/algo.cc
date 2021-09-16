string from_decimal(long long x, int base, bool upper_case=false) {
  /* O(log x) */
  assert(2 <= base && base <= 9+26);
  if(x == 0) return "0";
  string r;
  while(x) {
    char u = x%base;
    r.push_back((u<10) ? (u+'0') : upper_case ? (u-10+'A') : (u-10+'a'));
    x /= base;
  }
  reverse(r.begin(), r.end());
  return r;
}

long long to_decimal(const string& x, int base) {
  /* O(|x|) */
  assert(2 <= base && base <= 9+26);
  long long r = 0, p = 1;
  for(int i=x.size()-1; i>=0; --i) { 
    assert(('0' <= x[i] && x[i] <= min('9', char('0'+base-1))) || ('a' <= x[i] && x[i] <= char('a'-11+base)) || ('A' <= x[i] && x[i] <= char('A'-11+base)));
    int d = (x[i] >= 'a') ? (x[i]-'a'+10) : (x[i] >= 'A') ? (x[i]-'A'+10) : (x[i]-'0');
    r += p * d; p *= base;
  }
  return r;
}

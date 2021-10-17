vector<string> split(const string &s, char delimiter, bool keep_empty=false) {
  vector<string> r; string t;
  for(char c:s) {
    if(c==delimiter){if(!t.empty()||keep_empty) r.push_back(t); t.clear();}
    else t += c;
  }
  if (!t.empty()||keep_empty) r.push_back(t);
  return r;
}

string remove_char(string &s, char c) {
  string r;
  for (const auto i: s) if(i!=c) r.push_back(i);
  return r;
}

bool is_palindrome(const string& s) {
  int l = 0, r = s.size()-1;
  while(l<r) if(s[l++] != s[r--]) return false;
  return true;
}

string fill_left(const string& s, int length_after_filling, char c='0') {
  return string(length_after_filling - s.length(), c) + s;
}

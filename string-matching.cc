template<typename T>
struct StringMatching {
  const T& pattern;
  vector<int> f;
  StringMatching() = default;
  StringMatching(const T& pattern_): pattern(pattern_), f(vector<int>(pattern_.size()+1)) {
    /* O(|pattern|) */
    f[0] = -1;
    int j = -1;
    for (int i = 0; i < pattern.size(); ++i) {
      while (j != -1 && pattern[j] != pattern[i]) j = f[j];
      f[i+1] = ++j;
    }
  }
  int operator[](int i) { return f[i];}
  vector<int> findAll(const T& text) {
    /* O(|text|) */
    vector<int> index;
    int j = 0;
    for (int i = 0; i < text.size(); ++i) {
      while (j != -1 && pattern[j] != text[i]) j = f[j];
      if (++j == pattern.size()) {
        index.push_back(i-j+1);
        j = f[j];
      }
    }
    return index;
  }
};

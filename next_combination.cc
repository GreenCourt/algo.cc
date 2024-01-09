struct Combinations {
  // enumerate combinations in lexical order
  int n, r;
  vector<int> current;
  Combinations(int n, int r) : n(n), r(r) { /* O(r) */
    assert(n > 0 && r > 0 && r <= n);
    for (int i=0; i<r; ++i) current.push_back(i);
  }
  bool next() { /* O(r) */
    for (int i=r-1; i>=0; --i) if (current[i] < n - r + i) {
      int j = current[i] + 1;
      while (i < r) current[i++] = j++;
      return true;
    }
    return false;
  }
  int operator[](int i) { return current[i];}
};

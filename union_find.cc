struct UnionFind {
  vector<int> data;
  int number_of_groups;
  UnionFind(int size=0) : data(size, -1), number_of_groups(size) { }
  bool unite(int x, int y) {
    x = root(x); y = root(y);
    if(x==y) return false;
    if (data[y] < data[x]) swap(x, y);
    data[x] += data[y]; data[y] = x;
    number_of_groups--;
    return true;
  }
  bool same(int x, int y) { return root(x) == root(y); }
  int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
  int size(int x) { return -data[root(x)]; }
  vector<vector<int>> groups() { /* O(n) */
    int n = ssize(data);
    vector<int> r(n), group_size(n);
    for (int i = 0; i < n; i++) { r[i] = root(i); group_size[r[i]]++; }
    vector<vector<int>> result(n);
    for (int i = 0; i < n; i++) result[i].reserve(group_size[i]);
    for (int i = 0; i < n; i++) result[r[i]].push_back(i);
    result.erase(remove_if(result.begin(), result.end(), [&](const vector<int>& v) { return v.empty(); }), result.end());
    assert(ssize(result) == number_of_groups);
    return result;
  }
};

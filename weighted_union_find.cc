template<typename T=long long>
struct WeightedUnionFind {
  vector<int> data;
  vector<T> diff_parent;
  int number_of_groups;
  WeightedUnionFind(int size=0) : data(size, -1), diff_parent(size), number_of_groups(size) { }
  bool unite(int x, int y, T w) { /* weight(y) = weight(x) + w */
    w += diff_root(x); w -= diff_root(y);
    x = root(x); y = root(y);
    if(x==y) return diff(x,y)==w; /* return false if conflicted */
    if (data[y] < data[x]) swap(x, y), w=-w;
    data[x] += data[y]; data[y] = x;
    diff_parent[y] = w;
    number_of_groups--;
    return true;
  }
  bool same(int x, int y) { return root(x) == root(y); }
  int root(int x) {
    if(data[x] < 0) return x;
    int r = root(data[x]);
    diff_parent[x] += diff_parent[data[x]];
    return data[x] = r;
  }
  int size(int x) { return -data[root(x)]; }
  T diff_root(int x) { root(x); return diff_parent[x]; }
  T diff(int x, int y) {
    assert(same(x,y));
    return diff_root(y) - diff_root(x);
  }
  vector<vector<int>> groups() {
    int n = data.size();
    vector<int> r(n), group_size(n);
    for (int i = 0; i < n; i++) { r[i] = root(i); group_size[r[i]]++; }
    vector<vector<int>> result(n);
    for (int i = 0; i < n; i++) result[i].reserve(group_size[i]);
    for (int i = 0; i < n; i++) result[r[i]].push_back(i);
    result.erase(remove_if(result.begin(), result.end(), [&](const vector<int>& v) { return v.empty(); }), result.end());
    assert(result.size() == number_of_groups);
    return result;
  }
};

template<typename T>
struct Compress1D {
  vector<T> origin; // origin[compressed[i]] = input[i]
  vector<T> compressed;
  Compress1D() {}
  Compress1D(vector<T> const &input) {
    /* O(n log n) */
    vector<T> origin(input);
    sort(origin.begin(), origin.end());
    origin.erase(unique(origin.begin(), origin.end()), origin.end());
    int n = input.size();
    compressed.resize(n);
    for (int i=0;i<n;i++)
      compressed[i] = lower_bound(origin.begin(), origin.end(), input[i]) - origin.begin();
  }
};

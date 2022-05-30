uint64_t get_hash(uint64_t x) {
  auto splitmix64 = [](uint64_t x) -> uint64_t {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  };
  static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
  return splitmix64(x + FIXED_RANDOM);
}

template<typename T>
struct ZobristHashSet {
  set<T> s;
  uint64_t hash = 0;
  ZobristHashSet() = default;
  void insert(T x) { /* O(log n) */
    if(s.count(x)) return;
    s.insert(x);
    hash ^= get_hash(x);
  }
  void erase(T x) { /* O(log n) */
    if(!s.count(x)) return;
    s.erase(x);
    hash ^= get_hash(x);
  }
  size_t size() { return s.size(); } /* O(1) */
  bool contains(T x) { return bool(s.count(x)); } /* O(1) */
  bool operator==(const ZobristHashSet &z) const { return (s.size() == z.s.size()) && (hash == z.hash); } /* O(1) */
  bool operator!=(const ZobristHashSet &z) const { return (s.size() != z.s.size()) || (hash != z.hash); } /* O(1) */
};

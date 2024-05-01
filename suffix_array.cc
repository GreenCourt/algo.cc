vector<int> sa_is(vector<int>& seq, int bucket_max) {
  /* O(n) = O(|seq| + bucket_max) */
  if(seq.size() == 0) return {};
  if(seq.size() == 1) return {0};
  if(seq.size() == 2) return (seq[0] < seq[1]) ? vector({0,1}) : vector({1,0});

  seq.push_back(0); // sentinel (will be removed later)
  int n = seq.size();
  bucket_max++;
  constexpr bool Stype = true, Ltype = false;
  vector<bool> type(n);
  type[n-1] = Stype;
  for(int i=n-2; i>=0; --i) type[i] = (seq[i] < seq[i+1]) ? Stype : (seq[i] > seq[i+1]) ? Ltype : type[i+1];

  int bucket_size = bucket_max + 1;
  vector bucket(bucket_size, 0);

  for(int i=0; i<n; ++i) bucket[seq[i]]++;
  vector bucket_cumulative(bucket_size+1, 0);
  for(int i=0; i<bucket_size; ++i) bucket_cumulative[i+1] = bucket_cumulative[i] + bucket[i];

  vector<int> sa(n); // suffix array

  auto is_lms = [&](int index) { return (index > 0) && (type[index] == Stype) && (type[index-1] == Ltype); };

  auto induce_sort = [&] (const vector<int>& lms) {
    fill(sa.begin(), sa.end(), -1);
    vector insertion_count(bucket_size, 0);

    for(auto it = lms.rbegin(); it!=lms.rend(); it++) {
      int c = seq[*it];
      sa[bucket_cumulative[c+1] - 1 - insertion_count[c]] = *it;
      insertion_count[c]++;
    }

    insertion_count.assign(bucket_size, 0);
    for(int i=0; i<n; ++i) if(sa[i] > 0 && type[sa[i]-1] == Ltype) {
      int c = seq[sa[i]-1];
      sa[bucket_cumulative[c] + insertion_count[c]] = sa[i]-1;
      insertion_count[c]++;
    }

    insertion_count.assign(bucket_size, 0);
    for(int i=n-1; i>=0; --i) if(sa[i] > 0 && type[sa[i]-1] == Stype) {
      int c = seq[sa[i]-1];
      sa[bucket_cumulative[c+1] - 1 - insertion_count[c]] = sa[i]-1;
      insertion_count[c]++;
    }
  };

  int number_of_lms = 0;
  for(int i=0; i<n; ++i) if(is_lms(i)) number_of_lms++;

  vector<int> lms;
  lms.reserve(number_of_lms);
  for(int i=0; i<n; ++i) if(is_lms(i)) lms.push_back(i);
  induce_sort(lms);

  if(number_of_lms > 1) {
    vector<int> lms_sorted;
    lms.reserve(number_of_lms);
    assert(sa[0] == n-1);
    for(int i=0; i<n; ++i) if(is_lms(sa[i])) lms_sorted.push_back(sa[i]);

    vector<int> input_rec(n,-1);
    int unq = 0;
    input_rec[n-1] = unq+1;
    assert(lms_sorted.front() == n-1);
    for(int i=1; i<number_of_lms; ++i) {
      int a = lms_sorted[i];
      int b = lms_sorted[i-1];
      bool same = true;
      for(int step=0; ; ++step) {
        if(seq[a+step] != seq[b+step] || is_lms(a+step) != is_lms(b+step)) { same = false; break; }
        if(step>0 && is_lms(a+step) && is_lms(b+step)) break;
      }
      unq += !same;
      input_rec[a] = unq+1;
    }
    {
      int pos = 0;
      for(int i=0; i<n; ++i) if(input_rec[i] != -1) input_rec[pos++] = input_rec[i]; 
      input_rec.erase(input_rec.begin() + pos, input_rec.end());
      assert(input_rec.size() == number_of_lms);
    }

    vector<int> rec_sa;
    if(unq == number_of_lms) for(int i=0; i<n; ++i) sa[input_rec[i]] = i;
    else rec_sa = sa_is(input_rec, unq);

    for(int i=0; i<number_of_lms; ++i) lms_sorted[i] = lms[rec_sa[i]];
    assert(lms_sorted.size() == number_of_lms);
    induce_sort(lms_sorted);
  }
  sa.erase(sa.begin()); // O(N)
  seq.pop_back();
  return sa;
}

template<class T>
struct SuffixArray {
  SuffixArray() = default;
  const T &sequence;
  vector<int> suffix_array;
  int operator[](int i) const { return suffix_array[i]; }
  size_t size() const { return sequence.size(); }

  SuffixArray(const string& sequence_) : sequence(sequence_) {
    /* O(n) */
    int n = sequence.size();
    vector<int> in(n);
    for(int i=0; i<n; ++i) in[i] = sequence[i];
    suffix_array = sa_is(in, 255);
  }

  template <typename S>
  SuffixArray(const vector<S>& sequence_) : sequence(sequence_) {
    /* O(n log n) */
    int n = sequence.size();
    // compression
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int l, int r) { return sequence[l] < sequence[r]; });
    vector<int> in(n);
    int unq = 0;
    for (int i = 0; i < n; i++) {
      if (i && sequence[idx[i - 1]] != sequence[idx[i]]) unq++;
      in[idx[i]] = unq+1;
    }
    suffix_array = sa_is(in, unq);
  }

  int find(const T& pattern) {
    // O( |pattern| * log(|sequence|) )
    // return starting position of given pattern in the sequence
    // return -1 if not found
    int psize = pattern.size(), ssize = sequence.size();
    auto compare = [&] (int start) {
      for(int i = 0; i < psize; i++) {
        if(start + i == ssize) return -1;
        if(pattern[i] < sequence[start + i]) return  1;
        if(pattern[i] > sequence[start + i]) return -1;
      }
      return 0;
    };
    int l = -1, r = sequence.size();
    while(r-l > 1) {
      int m = l + (r-l) / 2;
      if(compare(suffix_array[m]) <= 0) l = m;
      else r = m;
    }
    return (l >= 0 && (compare(suffix_array[l]) == 0)) ? suffix_array[l] : -1;
  }
};
SuffixArray(const string &sequence) -> SuffixArray<string>;
template <typename S>
SuffixArray(const vector<S> &sequence) -> SuffixArray<vector<S>>;

template<class T>
vector<int> longest_common_prefix_array(const SuffixArray<T> &sa) {
  /* O(n) */
  int n = sa.size();
  assert(n >= 1);
  vector<int> rank(n);
  for (int i = 0; i < n; i++) rank[sa[i]] = i;
  vector<int> lcp(n - 1);
  int h = 0;
  for (int i = 0; i < n; i++) {
    if (h > 0) h--;
    if (rank[i] == 0) continue;
    int j = sa[rank[i] - 1];
    for (; j + h < n && i + h < n; h++) if (sa.sequence[j + h] != sa.sequence[i + h]) break;
    lcp[rank[i] - 1] = h;
  }
  return lcp;
}

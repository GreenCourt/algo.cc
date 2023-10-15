struct Fibonacci {
  vector<long long> fib;
  constexpr static int size = 93; // limited by long long
  Fibonacci() : fib(size) {
    fib[0] = 0, fib[1] = 1;
    for(int i=2; i<size; ++i) fib[i] = fib[i-1] + fib[i-2];
  }
  vector<int> zeckendorf_representation(long long x) {
    // return a sequence {a,b, ..., c} 
    // s.t  x = fib[a] + fib[b] + ... + fib[c].
    //      2 <= a < b < ... < c
    assert(x >= 0 and x - fib[size-2] < fib[size-1]);
    vector<int> r;
    while(x) {
      auto it = prev(upper_bound(fib.begin(), fib.end(), x));
      x -= *it;
      r.push_back(it - fib.begin());
    }
    reverse(r.begin(), r.end());
    return r;
  }
};

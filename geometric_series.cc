inline long long geometric_series_sum(long long first, long long last, long long n) {
  return (first + last) * n / 2;
}

inline long long geometric_series_sum2(long long first, long long diff, long long n) {
  long long last = first + (n-1)*diff;
  return geometric_series_sum(first, last, n);
}

inline long long geometric_series_sum3(long long first, long long last, long long diff) {
  long long n = (last - first) / diff + 1;
  return geometric_series_sum(first, last, n);
}

inline long long geometric_series_sum4(long long last, long long diff, long long n) {
  long long first = last - (n-1)*diff;
  return geometric_series_sum(first, last, n);
}

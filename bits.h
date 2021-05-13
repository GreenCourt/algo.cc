inline unsigned long long extract_msb(unsigned long long x) { return 1LL << ((x==0) ? 0 : 64 - __builtin_clzll(x)-1); }
inline unsigned long long extract_lsb(unsigned long long x) { return 1LL << (__builtin_ffsll(x)-1); }
inline int msb_position(unsigned long long x) { return (x==0) ? 0 : 64 - __builtin_clzll(x); }
inline int lsb_position(unsigned long long x) { return __builtin_ffsll(x); }

inline int bit_rotate_right(int bits, int rot, int length) { return (bits>>rot) + ((((1<<rot)-1) & bits) << (length - rot)); }
inline int bit_rotate_left(int bits, int rot, int length) { return ((bits<<rot)+(bits >> (length-rot))) & ((1<<length)-1); }
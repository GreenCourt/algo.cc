const double EPS=1e-9, PI = acos(-1);
inline int sgn(const double a) {return (a < -EPS ? -1 : (a > EPS ? +1 : 0));}

using Point = complex<double>;

struct Line {
  Point s,t;
  Line() = default;
  Line(Point s, Point t) : s(s), t(t) {}
  Line(double A, double B, double C) { // Ax+By=C
    if(sgn(A)==0) s = Point(0, C / B), t = Point(1, C / B);
    else if(sgn(B)==0) s = Point(C / A, 0), t = Point(C / A, 1);
    else s = Point(0, C / B), t = Point(C / A, 0);
  }
  friend ostream &operator<<(ostream &os, Line &p) { return os << p.s << " --> " << p.t; }
  friend istream &operator>>(istream &is, Line &p) { return is >> p.s >> p.t; }
};

struct Segment {
  Point s,t;
  Segment() = default;
  Segment(const Point& s, const Point& t) : s(s), t(t) {}
  friend ostream &operator<<(ostream &os, Segment &p) { return os << p.s << " --> " << p.t; }
  friend istream &operator>>(istream &is, Segment &p) { return is >> p.s >> p.t; }
};

using Polygon = vector<Point>;

istream& operator>>(istream& is, Point& p) {double x,y; is >> x >> y; p = Point(x,y); return is; }
ostream& operator<<(ostream& os, const Point& p) {os<<"("<<p.real()<<","<<p.imag()<<")"; return os;}

Point operator*(const Point &p, const double &d) { return Point(p.real()*d, p.imag()*d); }
Point rotate(double theta_radian, const Point &p) {
  return Point(cos(theta_radian) * p.real() - sin(theta_radian) * p.imag(),
      sin(theta_radian) * p.real() + cos(theta_radian) * p.imag());
}

namespace std {
#if 1 // compare by coordinates
  bool operator<(const Point& a, const Point& b) { return sgn(real(a-b)) ? real(a-b) < 0 : sgn(imag(a-b)) < 0; }
  bool operator>(const Point& a, const Point& b) { return sgn(real(a-b)) ? real(a-b) > 0 : sgn(imag(a-b)) > 0; }
  bool operator==(const Point& a, const Point& b) { return sgn(real(a-b)) == 0 && sgn(imag(a-b)) == 0; }
#else // compare by arguments
  bool operator<(const Point& a, const Point& b) { return sgn(arg(a)-arg(b))<0; }
  bool operator>(const Point& a, const Point& b) { return sgn(arg(a)-arg(b))>0; }
  bool operator==(const Point& a, const Point& b) { return sgn(arg(a)-arg(b))==0;}
#endif
}

double dot(const Point &a, const Point &b){return a.real()*b.real()+a.imag()*b.imag();}    // |a||b|cos()
double cross(const Point &a, const Point &b) {return a.real()*b.imag()-a.imag()*b.real();} // |a||b|sin()

bool is_parallel(const Point &a, const Point &b) {return sgn(cross(a,b)) == 0;}
bool is_parallel(const Line &a, const Line &b) {return sgn(cross(a.t - a.s, b.t - b.s)) == 0;}
bool is_parallel(const Segment &a, const Segment &b) {return sgn(cross(a.t - a.s, b.t - b.s)) == 0;}
bool is_parallel(const Line &a, const Segment &b) {return sgn(cross(a.t - a.s, b.t - b.s)) == 0;}

bool is_orthogobal(const Point &a, const Point &b) {return sgn(dot(a,b)) == 0;}
bool is_orthogobal(const Line &a, const Line &b) {return sgn(dot(a.t - a.s, b.t - b.s)) == 0;}
bool is_orthogobal(const Segment &a, const Segment &b) {return sgn(dot(a.t - a.s, b.t - b.s)) == 0;}
bool is_orthogobal(const Line &a, const Segment &b) {return sgn(dot(a.t - a.s, b.t - b.s)) == 0;}

int ccw(const Point &s, Point t, Point x) {
  t = t - s, x = x - s;
  if(sgn(cross(t, x)) > 0) return +1;    // COUNTER_CLOCKWISE : x is right-side of s-t
  if(sgn(cross(t, x)) < 0) return -1;    // CLOCKWISE         : x is left-side of s-t
  if(sgn(dot(t, x) < 0)) return +2;      // ONLINE_BACK       : line up x-s-t
  if(sgn(norm(t)-norm(x))<0) return -2;  // ONLINE_FRONT      : line up s-t-x
  return 0;                              // ON_SEGMENT        : line up s-x-t
}

double radian2degree(const double &radian) {return radian * 180.0 / PI;}
double degree2radian(const double &degree) {return degree * PI / 180.0;}

Point projection(const Line &l, const Point &p){return l.s+(dot(p-l.s, l.t-l.s)/norm(l.t-l.s))*(l.t-l.s);}
Point reflection(const Line &l, const Point &p){return p+(projection(l,p)-p)*2.0;}
bool same(const Line &a, const Line &b){return (sgn(cross(a.t-a.s, b.t-b.s))==0)&&(sgn(cross(a.t-a.s, b.s-a.s)==0));}

bool intersect(const Line &l, const Point &p) { return abs(ccw(l.s, l.t, p)) != 1; }
bool intersect(const Line &a, const Line &b) { return sgn(cross(a.t-a.s, b.t-b.s))!=0 || sgn(cross(a.t-a.s, b.t-a.s))==0; }
bool intersect(const Segment &s, const Point &p) { return ccw(s.s, s.t, p) == 0; }
bool intersect(const Line &l, const Segment &s) { return sgn(cross(l.t-l.s, s.s-l.s)*cross(l.t-l.s, s.t-l.s)) <= 0; }
bool intersect(const Segment &a, const Segment &b) {
  return ccw(a.s, a.t, b.s)*ccw(a.s, a.t, b.t) <= 0 && ccw(b.s, b.t, a.s)*ccw(b.s, b.t, a.t) <= 0;
}

Point cross_point(const Segment& s1, const Segment& s2) {
  assert(intersect(s1,s2));
  assert(!is_parallel(s1, s2));
  return s1.s + abs(cross(s2.t - s1.s, s2.t-s2.s) / cross(s1.t-s1.s, s2.t-s2.s)) * (s1.t-s1.s);
}
Point cross_point(const Line& l1, const Line& l2) {
  assert(!is_parallel(l1, l2));
  return l1.s + (cross(l2.t-l1.s, l2.t-l2.s) / cross(l1.t-l1.s, l2.t-l2.s)) * (l1.t-l1.s);
}
Point cross_point(const Line& l, const Segment& s) {
  assert(intersect(l,s));
  return cross_point(l, Line(s.s, s.t));
}

double distance(const Point& a, const Point& b) { return abs(a - b); }
double distance(const Line& l, const Point& p){return abs(cross(l.t-l.s, p-l.s)) / abs(l.t-l.s);}
double distance(const Segment& s, const Point& p){
  if (sgn(dot(s.t-s.s,p-s.s)) < 0 || sgn(dot(s.s-s.t,p-s.t) < 0)) return min(abs(s.s-p), abs(s.t-p));
  return abs(cross(s.t-s.s, p-s.s)) / abs(s.t-s.s);
}
double distance(const Segment& a, const Segment& b){
  if(intersect(a,b)) return 0;
  return min({distance(a, b.s), distance(a, b.t), distance(b, a.s), distance(b, a.t)});
}
double distance(const Line &a, const Line &b) { return intersect(a, b) ? 0 : distance(a, b.s); }
double distance(const Line &l, const Segment &s) {
  if(intersect(l, s)) return 0;
  return min(distance(l, s.s), distance(l, s.t));
}

double signed_area(const Polygon& p) {
  /* O(N) */
  /* return positive value if clockwise else negative value */
  double a = 0; int n = p.size();
  for(int i=0; i<n-1; ++i) a += cross(p[i], p[i+1]);
  a += cross(p[n-1], p[0]);
  a /= 2;
  return a;
}

bool is_convex(const Polygon& p) { /* O(N) */
  int n = p.size();
  for(int i=0;i<n;i++) 
    if(ccw(p[(i+n-1)%n], p[i], p[(i+1)%n])==-1) return false;
  return true;
}

int contains(const Polygon& poly, const Point& p) {
  /* O(N) */
  // return 0 if p is outside of poly
  //        1 if p is on the edge of poly
  //        2 if p is inside of poly
  bool inside = false; int n = poly.size();
  for(int i=0; i<n; ++i) {
    Point a = poly[i] - p, b = poly[(i+1)%n] - p;
    if(a.imag() > b.imag()) swap(a,b);
    if(sgn(a.imag()) <= 0 && 0 < b.imag() && cross(a,b) < 0) inside = !inside;
    if(sgn(cross(a,b)) == 0 && sgn(dot(a,b)) <= 0) return 1; // on the edge
  }
  return inside ? 2 : 0;
}

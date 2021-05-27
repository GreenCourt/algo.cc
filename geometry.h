using Float = double;
const Float EPS=1e-9, PI = acos(-1.0L);
inline int sgn(const Float a) {return (a < -EPS ? -1 : (a > EPS ? +1 : 0));}

using Point = complex<Float>;
using Vector = Point;
istream& operator>>(istream& is, Point& p) {Float x,y; is >> x >> y; p = Point(x,y); return is; }
ostream& operator<<(ostream& os, const Point& p) {os<<"("<<p.real()<<","<<p.imag()<<")"; return os;}

struct Line {
  Point s,t;
  Line() = default;
  Line(Point s, Point t) : s(s), t(t) {}
  Line(Float A, Float B, Float C) { // Ax+By=C
    if(sgn(A)==0) s = Point(0, C / B), t = Point(1, C / B);
    else if(sgn(B)==0) s = Point(C / A, 0), t = Point(C / A, 1);
    else s = Point(0, C / B), t = Point(C / A, 0);
  }
  friend ostream &operator<<(ostream &os, Line &p) { return os << p.s << " --> " << p.t; }
};

struct Segment {
  Point s,t;
  Segment() = default;
  Segment(const Point& s, const Point& t) : s(s), t(t) {}
  friend ostream &operator<<(ostream &os, Segment &p) { return os << p.s << " --> " << p.t; }
};

using Polygon = vector<Point>;

struct Circle {
  Point p; Float r;
  Circle() = default;
  Circle(Point p, Float r) : p(p), r(r) {}
};

Point operator*(const Point &p, const Float &d) { return Point(p.real()*d, p.imag()*d); }
Point operator/(const Point &p, const Float &d) { return Point(p.real()/d, p.imag()/d); }
Point rotate(Float theta_radian, const Point &p) {
  return Point(cos(theta_radian) * p.real() - sin(theta_radian) * p.imag(),
      sin(theta_radian) * p.real() + cos(theta_radian) * p.imag());
}
Point rotate90(const Point &p) {return Point(-p.imag(), p.real());}

inline bool coordinate_lt(const Point& a, const Point& b) { return sgn(real(a-b)) ? real(a-b) < 0 : sgn(imag(a-b)) < 0; }
inline bool coordinate_gt(const Point& a, const Point& b) { return sgn(real(a-b)) ? real(a-b) > 0 : sgn(imag(a-b)) > 0; }
inline bool coordinate_eq(const Point& a, const Point& b) { return sgn(real(a-b)) == 0 && sgn(imag(a-b)) == 0; }
inline bool arg_lt(const Point& a, const Point& b) { return sgn(arg(a)-arg(b))<0; }
inline bool arg_gt(const Point& a, const Point& b) { return sgn(arg(a)-arg(b))>0; }
inline bool arg_eq(const Point& a, const Point& b) { return sgn(arg(a)-arg(b))==0;}

namespace std {
#if 1 // compare by coordinates
  bool operator<(const Point& a, const Point& b) { return coordinate_lt(a,b); }
  bool operator>(const Point& a, const Point& b) { return coordinate_gt(a,b); }
  bool operator==(const Point& a, const Point& b) { return coordinate_eq(a,b); }
#else // compare by arguments
  bool operator<(const Point& a, const Point& b) { return arg_lt(a,b);}
  bool operator>(const Point& a, const Point& b) { return arg_gt(a,b);}
  bool operator==(const Point& a, const Point& b) { return arg_eq(a,b);}
#endif
}

Float dot(const Point &a, const Point &b){return a.real()*b.real()+a.imag()*b.imag();}    // |a||b|cos()
Float cross(const Point &a, const Point &b) {return a.real()*b.imag()-a.imag()*b.real();} // |a||b|sin()

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

Float radian2degree(const Float &radian) {return radian * 180.0 / PI;}
Float degree2radian(const Float &degree) {return degree * PI / 180.0;}

Point projection(const Line &l, const Point &p){return l.s+(dot(p-l.s, l.t-l.s)/norm(l.t-l.s))*(l.t-l.s);}
Point projection(const Segment &l, const Point &p){return l.s+(dot(p-l.s, l.t-l.s)/norm(l.t-l.s))*(l.t-l.s);}
Point reflection(const Line &l, const Point &p){return p+(projection(l,p)-p)*2.0;}
bool same(const Line &a, const Line &b){return (sgn(cross(a.t-a.s, b.t-b.s))==0)&&(sgn(cross(a.t-a.s, b.s-a.s)==0));}

bool intersect(const Line &l, const Point &p) { return abs(ccw(l.s, l.t, p)) != 1; }
bool intersect(const Line &a, const Line &b) { return sgn(cross(a.t-a.s, b.t-b.s))!=0 || sgn(cross(a.t-a.s, b.t-a.s))==0; }
bool intersect(const Segment &s, const Point &p) { return ccw(s.s, s.t, p) == 0; }
bool intersect(const Line &l, const Segment &s) { return sgn(cross(l.t-l.s, s.s-l.s)*cross(l.t-l.s, s.t-l.s)) <= 0; }
bool intersect(const Segment &a, const Segment &b) {
  return ccw(a.s, a.t, b.s)*ccw(a.s, a.t, b.t) <= 0 && ccw(b.s, b.t, a.s)*ccw(b.s, b.t, a.t) <= 0;
}
int number_of_common_tangents(const Circle& c1, const Circle& c2);
int intersect(const Circle &c1, const Circle &c2) {
  int n = number_of_common_tangents(c1,c2);
  if(n==4) return n=0;
  if(n==3) return n=1;
  return n;
}
Float distance(const Line& l, const Point& p);
int intersect(const Circle &c, const Line &l) {
  Float d = distance(l, c.p);
  if(sgn(d - c.r) == 0) return 1;
  else if(sgn(d - c.r) < 0) return 2;
  else return 0;
}
int intersect(const Circle &c, const Segment &s) {
  if(sgn(norm(projection(s, c.p) - c.p) - c.r * c.r) > 0) return 0;
  auto d1 = abs(c.p - s.s), d2 = abs(c.p - s.t);
  if(sgn(d1-c.r) < 0 && sgn(d2-c.r) < 0) return 0;
  if((sgn(d1-c.r) < 0 && sgn(d2-c.r) >= 0) || (sgn(d1-c.r) >= 0 && sgn(d2-c.r) < 0)) return 1;
  const Point h = projection(s, c.p);
  if(sgn(dot(s.s - h, s.t - h)) < 0) return 2;
  if(sgn(d1-c.r) == 0 || sgn(d2-c.r) == 0) return 1;
  return 0;
}

Float distance(const Point& a, const Point& b) { return abs(a - b); }
Float distance(const Line& l, const Point& p){return abs(cross(l.t-l.s, p-l.s)) / abs(l.t-l.s);}
Float distance(const Segment& s, const Point& p){
  if (sgn(dot(s.t-s.s,p-s.s)) < 0 || sgn(dot(s.s-s.t,p-s.t) < 0)) return min(abs(s.s-p), abs(s.t-p));
  return abs(cross(s.t-s.s, p-s.s)) / abs(s.t-s.s);
}
Float distance(const Segment& a, const Segment& b){
  if(intersect(a,b)) return 0;
  return min({distance(a, b.s), distance(a, b.t), distance(b, a.s), distance(b, a.t)});
}
Float distance(const Line &a, const Line &b) { return intersect(a, b) ? 0 : distance(a, b.s); }
Float distance(const Line &l, const Segment &s) {
  if(intersect(l, s)) return 0;
  return min(distance(l, s.s), distance(l, s.t));
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
vector<Point> cross_point(const Circle& c, const Line& l) {
  if(sgn(distance(l, c.p) - c.r) > 0) return vector<Point>();
  Point pr = projection(l, c.p);
  if(sgn(distance(l, c.p) - c.r) == 0) return {pr};
  Vector e = (l.t-l.s) / abs(l.t-l.s);;
  Float base=sqrt(c.r*c.r-norm(pr-c.p));
  return {pr+e*base, pr-e*base};
}
vector<Point> cross_point(const Circle &c, const Segment &s) {
  Line l = Line(s.s, s.t);
  int is = intersect(c, s);
  if(is == 0) return {};
  auto cp = cross_point(c, l);
  if(is == 2) {
    // order in s.s - cp[0] - cp[1] - s.t
    if(ccw(s.s, cp.back(), cp.front()) == -2) swap(cp[0],cp[1]);
    return cp;
  }
  if(ccw(s.s, s.t, cp[0]) == 0 ) return {cp[0]};
  else return {cp[1]};
}
vector<Point> cross_point(const Circle& c1, const Circle& c2) {
  Float d = abs(c1.p-c2.p);
  Float rc = (d*d + c1.r*c1.r - c2.r*c2.r) / (2*d);
  Float rs = sqrt(c1.r*c1.r-rc*rc);
  Vector e = (c2.p-c1.p) / d;
  if(isnan(rs)) return vector<Point>();
  if(sgn(rs==0)) return {c1.p + e * Vector(rc,rs)};
  return {c1.p + e * Vector(rc,rs), c1.p + e * Vector(rc,-rs)};
}

Float signed_area(const Polygon& p) {
  /* O(N) */
  /* return positive value if clockwise else negative value */
  Float a = 0; int n = p.size();
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
    Vector a = poly[i] - p, b = poly[(i+1)%n] - p;
    if(a.imag() > b.imag()) swap(a,b);
    if(sgn(a.imag()) <= 0 && 0 < b.imag() && cross(a,b) < 0) inside = !inside;
    if(sgn(cross(a,b)) == 0 && sgn(dot(a,b)) <= 0) return 1; // on the edge
  }
  return inside ? 2 : 0;
}

bool contains(const Circle &c, const Point &p) {
  Float d = abs(p - c.p);
  if (sgn(d - c.r) == 0) return 2;     // on the edge
  else if (sgn(d - c.r) < 0) return 1; // inside
  else return 0;                       // outside
}

int number_of_common_tangents(const Circle& c1, const Circle& c2) {
  Float d = abs(c1.p-c2.p);
  if(sgn(d-(c1.r+c2.r)) > 0 )                           return 4; // no intersection (outside)
  else if(sgn(d-(c1.r+c2.r)) == 0 )                     return 3; // one intersection (circumscribed)
  else if(sgn((c1.r+d)-c2.r)==0||sgn((c2.r+d)-c1.r)==0) return 1; // one intersection (inscribed)
  else if(sgn((c1.r+d)-c2.r)<0||sgn((c2.r+d)-c1.r)<0)   return 0; // no intersection (inside)
  else                                                  return 2; // two intersection
}

Circle inscribed_circle(const Point& p1, const Point& p2, const Point& p3) {
  // return the inscribed circle of a triangle
  Float d12 = abs(p1-p2), d23 = abs(p2-p3), d31 = abs(p3-p1);
  Point center((d23*p1.real() + d31*p2.real() + d12*p3.real())/(d12+d23+d31),
      (d23*p1.imag() + d31*p2.imag() + d12*p3.imag())/(d12+d23+d31));
  Float r = 2 * abs(signed_area({p1,p2,p3})) / (abs(p1-p2) + abs(p2-p3) + abs(p3-p1));
  return Circle(center, r);
}

Circle circumscribed_circle(const Point& p1, const Point& p2, const Point& p3) {
  // return the circumscribed circle of a triangle
  Line l12((p2+p1)/2, rotate90((p2-p1)/2) + (p2+p1)/2);
  Line l13((p3+p1)/2, rotate90((p3-p1)/2) + (p3+p1)/2);
  Point center = cross_point(l12,l13);
  Float r = abs(center - p1);
  return Circle(center, r);
}

vector<Point> tangent(const Circle &c, const Point &p) {return cross_point(c,Circle(p,sqrt(norm(c.p-p)-c.r*c.r)));}

vector<Line> tangent(Circle c1, Circle c2) {
  vector<Line> ret;
  if(c1.r < c2.r) swap(c1, c2);
  Float d = abs(c1.p - c2.p);
  if(sgn(d)==0) return ret;
  Point u = (c2.p - c1.p) / d;
  Point v = rotate90(u);
  for(int s : {-1, 1}) {
    Float h = (c1.r + s * c2.r) / d;
    if(sgn(1-h*h) == 0) {
      ret.emplace_back(c1.p + u * c1.r, c1.p + (u + v) * c1.r);
    }
    else if(1-h*h > 0) {
      Point uu = u * h, vv = v * sqrt(1-h*h);
      ret.emplace_back(c1.p + (uu + vv) * c1.r, c2.p - (uu + vv) * c2.r * s);
      ret.emplace_back(c1.p + (uu - vv) * c1.r, c2.p - (uu - vv) * c2.r * s);
    }
  }
  return ret;
}


Float intersection_area(const Circle &c, const Polygon &poly) {
  auto argument = [&] (const Point &from, const Point &to) {
    return atan2(cross(from, to), dot(from, to)); /* range [-pi, pi] */
  };
  Float area = 0;
  const int n = poly.size();
  for(int i=0;i<n;++i){
    const Point &p1 = poly[i] - c.p, &p2 = poly[(i + 1) % n] - c.p;
    if(abs(ccw(c.p, p1, p2)) != 1) continue;
    if(sgn(abs(p1)-c.r) < 0 && sgn(abs(p2) - c.r) < 0) {
      area += 0.5 * cross(p1, p2);
    }
    else if (sgn(abs(p1)-c.r) < 0) {
      const vector<Point> cp = cross_point(c, Segment(p1, p2));
      area += 0.5 * cross(p1, cp.front());
      area += 0.5 * c.r * c.r * argument(cp.front(),p2);
    }
    else if (sgn(abs(p2)-c.r) < 0) {
      const vector<Point> cp = cross_point(c, Segment(p1, p2));
      area += 0.5 * c.r * c.r * argument(p1,cp.front());
      area += 0.5 * cross(cp.front(), p2);
    }
    else {
      vector<Point> cp = cross_point(c, Segment(p1, p2));
      if (cp.size() == 0) {
        area += 0.5 * c.r * c.r * argument(p1,p2);
      }
      else {
        area += 0.5 * c.r * c.r * argument(p1,cp.front());
        area += 0.5 * cross(cp.front(), cp.back());
        area += 0.5 * c.r * c.r * argument(cp.back(),p2);
      }
    }
  }
  return area;
}

Float intersection_area(const Circle &c1, const Circle &c2) {
  int ct = number_of_common_tangents(c1,c2);
  if(ct==3 || ct==4) return 0;
  if(ct==0 || ct==1) return min(c1.r*c1.r*PI, c2.r*c2.r*PI);
  auto cp = cross_point(c1,c2);
  assert(cp.size() == 2);
  Float d = abs(c1.p - c2.p), r1 = c1.r, r2 = c2.r;
  Float area = 0;
  Float a1 = acos((r1*r1-r2*r2+d*d)/(2*d*r1));
  Float a2 = acos((r2*r2-r1*r1+d*d)/(2*d*r2));
  area += r1*r1*a1;
  area += r2*r2*a2;
  area -= r1*sin(a1) * r1*cos(a1);
  area -= r2*sin(a2) * r2*cos(a2);
  return area;
}

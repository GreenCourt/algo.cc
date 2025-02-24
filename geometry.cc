using Float = double;
const Float EPS=1e-9;
inline int sgn(const Float a) {return (a < -EPS ? -1 : (a > EPS ? +1 : 0));}

using Point = complex<Float>;
using Vector = Point;
istream& operator>>(istream& is, Point& p) {Float x,y; is >> x >> y; p = Point(x,y); return is; }
ostream& operator<<(ostream& os, const Point& p) {os<<"("<<p.real()<<","<<p.imag()<<")"; return os;}

struct Line : public array<Point, 2> {
  Line() = default;
  Line(const Point &p1, const Point &p2) { (*this)[0] = p1, (*this)[1] = p2; }
  Line(Float A, Float B, Float C) { // Ax+By=C
    if(sgn(A)==0) (*this)[0] = Point(0, C / B), (*this)[1] = Point(1, C / B);
    else if(sgn(B)==0) (*this)[0] = Point(C / A, 0), (*this)[1] = Point(C / A, 1);
    else (*this)[0] = Point(0, C / B), (*this)[1] = Point(C / A, 0);
  }
  friend ostream &operator<<(ostream &os, Line &p) { return os << p[0] << " --> " << p[1]; }
};

struct Segment : public array<Point, 2> {
  Segment() = default;
  Segment(const Point &p1, const Point &p2) { (*this)[0] = p1, (*this)[1] = p2; }
  friend ostream &operator<<(ostream &os, Segment &p) { return os << p[0] << " --> " << p[1]; }
};

using Polygon = vector<Point>;

struct Circle {
  Point center; Float r;
  Circle() = default;
  Circle(const Point& center_, Float r_) : center(center_), r(r_) {}
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
bool is_parallel(const Line &a, const Line &b) {return sgn(cross(a[1] - a[0], b[1] - b[0])) == 0;}
bool is_parallel(const Segment &a, const Segment &b) {return sgn(cross(a[1] - a[0], b[1] - b[0])) == 0;}
bool is_parallel(const Line &a, const Segment &b) {return sgn(cross(a[1] - a[0], b[1] - b[0])) == 0;}

bool is_orthogobal(const Point &a, const Point &b) {return sgn(dot(a,b)) == 0;}
bool is_orthogobal(const Line &a, const Line &b) {return sgn(dot(a[1] - a[0], b[1] - b[0])) == 0;}
bool is_orthogobal(const Segment &a, const Segment &b) {return sgn(dot(a[1] - a[0], b[1] - b[0])) == 0;}
bool is_orthogobal(const Line &a, const Segment &b) {return sgn(dot(a[1] - a[0], b[1] - b[0])) == 0;}

int ccw(const Point &s, Point t, Point x) {
  t = t - s, x = x - s;
  if(sgn(cross(t, x)) > 0) return +1;    // COUNTER_CLOCKWISE : x is left-side of s-t
  if(sgn(cross(t, x)) < 0) return -1;    // CLOCKWISE         : x is right-side of s-t
  if(sgn(dot(t, x) < 0)) return +2;      // ONLINE_BACK       : line up x-s-t
  if(sgn(norm(t)-norm(x))<0) return -2;  // ONLINE_FRONT      : line up s-t-x
  return 0;                              // ON_SEGMENT        : line up s-x-t
}

Float radian2degree(const Float &radian) {return radian * 180.0 / numbers::pi;}
Float degree2radian(const Float &degree) {return degree * numbers::pi / 180.0;}

Point projection(const Line &l, const Point &p){return l[0]+(dot(p-l[0], l[1]-l[0])/norm(l[1]-l[0]))*(l[1]-l[0]);}
Point projection(const Segment &l, const Point &p){return l[0]+(dot(p-l[0], l[1]-l[0])/norm(l[1]-l[0]))*(l[1]-l[0]);}
Point reflection(const Line &l, const Point &p){return p+(projection(l,p)-p)*2.0;}
bool same(const Line &a, const Line &b){return (sgn(cross(a[1]-a[0], b[1]-b[0]))==0)&&(sgn(cross(a[1]-a[0], b[0]-a[0]))==0);}

bool intersect(const Line &l, const Point &p) { return abs(ccw(l[0], l[1], p)) != 1; }
bool intersect(const Line &a, const Line &b) { return sgn(cross(a[1]-a[0], b[1]-b[0]))!=0 || sgn(cross(a[1]-a[0], b[1]-a[0]))==0; }
bool intersect(const Segment &s, const Point &p) { return ccw(s[0], s[1], p) == 0; }
bool intersect(const Line &l, const Segment &s) { return sgn(cross(l[1]-l[0], s[0]-l[0])*cross(l[1]-l[0], s[1]-l[0])) <= 0; }
bool intersect(const Segment &a, const Segment &b) {
  return ccw(a[0], a[1], b[0])*ccw(a[0], a[1], b[1]) <= 0 && ccw(b[0], b[1], a[0])*ccw(b[0], b[1], a[1]) <= 0;
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
  Float d = distance(l, c.center);
  if(sgn(d - c.r) == 0) return 1;
  else if(sgn(d - c.r) < 0) return 2;
  else return 0;
}
int intersect(const Circle &c, const Segment &s) {
  if(sgn(norm(projection(s, c.center) - c.center) - c.r * c.r) > 0) return 0;
  auto d1 = abs(c.center - s[0]), d2 = abs(c.center - s[1]);
  if(sgn(d1-c.r) < 0 && sgn(d2-c.r) < 0) return 0;
  if((sgn(d1-c.r) < 0 && sgn(d2-c.r) >= 0) || (sgn(d1-c.r) >= 0 && sgn(d2-c.r) < 0)) return 1;
  const Point h = projection(s, c.center);
  if(sgn(dot(s[0] - h, s[1] - h)) < 0) return 2;
  if(sgn(d1-c.r) == 0 || sgn(d2-c.r) == 0) return 1;
  return 0;
}

Float distance(const Point& a, const Point& b) { return abs(a - b); }
Float distance(const Line& l, const Point& p){return abs(cross(l[1]-l[0], p-l[0])) / abs(l[1]-l[0]);}
Float distance(const Segment& s, const Point& p){
  if (sgn(dot(s[1]-s[0],p-s[0])) < 0 || sgn(dot(s[0]-s[1],p-s[1]) < 0)) return min(abs(s[0]-p), abs(s[1]-p));
  return abs(cross(s[1]-s[0], p-s[0])) / abs(s[1]-s[0]);
}
Float distance(const Segment& a, const Segment& b){
  if(intersect(a,b)) return 0;
  return min({distance(a, b[0]), distance(a, b[1]), distance(b, a[0]), distance(b, a[1])});
}
Float distance(const Line &a, const Line &b) { return intersect(a, b) ? 0 : distance(a, b[0]); }
Float distance(const Line &l, const Segment &s) {
  if(intersect(l, s)) return 0;
  return min(distance(l, s[0]), distance(l, s[1]));
}

Point cross_point(const Segment& s1, const Segment& s2) {
  assert(intersect(s1,s2));
  assert(!is_parallel(s1, s2));
  return s1[0] + abs(cross(s2[1] - s1[0], s2[1]-s2[0]) / cross(s1[1]-s1[0], s2[1]-s2[0])) * (s1[1]-s1[0]);
}
Point cross_point(const Line& l1, const Line& l2) {
  assert(!is_parallel(l1, l2));
  return l1[0] + (cross(l2[1]-l1[0], l2[1]-l2[0]) / cross(l1[1]-l1[0], l2[1]-l2[0])) * (l1[1]-l1[0]);
}
Point cross_point(const Line& l, const Segment& s) {
  assert(intersect(l,s));
  return cross_point(l, Line(s[0], s[1]));
}
vector<Point> cross_point(const Circle& c, const Line& l) {
  if(sgn(distance(l, c.center) - c.r) > 0) return vector<Point>();
  Point pr = projection(l, c.center);
  if(sgn(distance(l, c.center) - c.r) == 0) return {pr};
  Vector e = (l[1]-l[0]) / abs(l[1]-l[0]);;
  Float base=sqrt(c.r*c.r-norm(pr-c.center));
  return {pr+e*base, pr-e*base};
}
vector<Point> cross_point(const Circle &c, const Segment &s) {
  Line l = Line(s[0], s[1]);
  int is = intersect(c, s);
  if(is == 0) return {};
  auto cp = cross_point(c, l);
  if(is == 2) {
    // order in s[0] - cp[0] - cp[1] - s[1]
    if(ccw(s[0], cp.back(), cp.front()) == -2) swap(cp[0],cp[1]);
    return cp;
  }
  if(ccw(s[0], s[1], cp[0]) == 0 ) return {cp[0]};
  else return {cp[1]};
}
vector<Point> cross_point(const Circle& c1, const Circle& c2) {
  Float d = abs(c1.center-c2.center);
  Float rc = (d*d + c1.r*c1.r - c2.r*c2.r) / (2*d);
  Float rs = sqrt(c1.r*c1.r-rc*rc);
  Vector e = (c2.center-c1.center) / d;
  if(isnan(rs)) return vector<Point>();
  if(sgn(rs)==0) return {c1.center + e * Vector(rc,rs)};
  return {c1.center + e * Vector(rc,rs), c1.center + e * Vector(rc,-rs)};
}

Float signed_area(const Polygon& p) {
  /* O(N) */
  /* return positive value if clockwise else negative value */
  assert(p.size());
  Float a = 0; int n = ssize(p);
  for(int i=0; i<n-1; ++i) a += cross(p[i], p[i+1]);
  a += cross(p[n-1], p[0]);
  a /= 2;
  return a;
}

bool is_convex(const Polygon& p) { /* O(N) */
  int n = ssize(p);
  for(int i=0;i<n;i++)
    if(ccw(p[(i+n-1)%n], p[i], p[(i+1)%n])==-1) return false;
  return true;
}

Polygon convex_cut(const Polygon &convex, const Point &s, const Point &t) { /* O(N) */
#ifdef _GLIBCXX_ASSERTIONS
  assert(is_convex(convex));
#endif
  // return the left side of the convex cut by the line from s to t
  int n = ssize(convex);
  Line line(s,t);
  Polygon left;
  for(int i=0; i<n; ++i) {
    const Point &p = convex[i], &q = convex[(i+1)%n];
    int ccw_p = ccw(s, t, p), ccw_q = ccw(s, t, q);
    if(ccw_p != -1) left.push_back(p);
    if(abs(ccw_q) == 1 && ccw_p * ccw_q < 0)
      left.push_back(cross_point(Line(p, q), line));
  }
  return left;
}

int contains(const Polygon& poly, const Point& p) {
  /* O(N) */
  // return 0 if p is outside of poly
  //        1 if p is on the edge of poly
  //        2 if p is inside of poly
  bool inside = false; int n = ssize(poly);
  for(int i=0; i<n; ++i) {
    Vector a = poly[i] - p, b = poly[(i+1)%n] - p;
    if(a.imag() > b.imag()) swap(a,b);
    if(sgn(a.imag()) <= 0 && 0 < b.imag() && cross(a,b) < 0) inside = !inside;
    if(sgn(cross(a,b)) == 0 && sgn(dot(a,b)) <= 0) return 1; // on the edge
  }
  return inside ? 2 : 0;
}

int contains(const Circle &c, const Point &p) {
  Float d = abs(p - c.center);
  if (sgn(d - c.r) == 0) return 1;     // on the edge
  else if (sgn(d - c.r) < 0) return 2; // inside
  else return 0;                       // outside
}

int number_of_common_tangents(const Circle& c1, const Circle& c2) {
  Float d = abs(c1.center-c2.center);
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

vector<Point> tangent(const Circle &c, const Point &p) {return cross_point(c,Circle(p,sqrt(norm(c.center-p)-c.r*c.r)));}

vector<Line> tangent(Circle c1, Circle c2) {
  vector<Line> ret;
  if(c1.r < c2.r) swap(c1, c2);
  Float d = abs(c1.center - c2.center);
  if(sgn(d)==0) return ret;
  Point u = (c2.center - c1.center) / d;
  Point v = rotate90(u);
  for(int s : {-1, 1}) {
    Float h = (c1.r + s * c2.r) / d;
    if(sgn(1-h*h) == 0) {
      ret.emplace_back(c1.center + u * c1.r, c1.center + (u + v) * c1.r);
    }
    else if(1-h*h > 0) {
      Point uu = u * h, vv = v * sqrt(1-h*h);
      ret.emplace_back(c1.center + (uu + vv) * c1.r, c2.center - (uu + vv) * c2.r * s);
      ret.emplace_back(c1.center + (uu - vv) * c1.r, c2.center - (uu - vv) * c2.r * s);
    }
  }
  return ret;
}


Float intersection_area(const Circle &c, const Polygon &poly) {
  auto argument = [&] (const Point &from, const Point &to) {
    return atan2(cross(from, to), dot(from, to)); /* range [-pi, pi] */
  };
  Float area = 0;
  const int n = ssize(poly);
  for(int i=0;i<n;++i){
    const Point &p1 = poly[i] - c.center, &p2 = poly[(i + 1) % n] - c.center;
    if(abs(ccw(c.center, p1, p2)) != 1) continue;
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
  if(ct==0 || ct==1) return min(c1.r*c1.r*numbers::pi, c2.r*c2.r*numbers::pi);
  auto cp = cross_point(c1,c2);
  assert(cp.size() == 2);
  Float d = abs(c1.center - c2.center), r1 = c1.r, r2 = c2.r;
  Float area = 0;
  Float a1 = acos((r1*r1-r2*r2+d*d)/(2*d*r1));
  Float a2 = acos((r2*r2-r1*r1+d*d)/(2*d*r2));
  area += r1*r1*a1;
  area += r2*r2*a2;
  area -= r1*sin(a1) * r1*cos(a1);
  area -= r2*sin(a2) * r2*cos(a2);
  return area;
}

#include <vector>
#include <math.h> 
#include <gmpxx.h>
#define PREC 10*1024

namespace N200644 {

class Point {
private:
    mpf_class _x, _y;
public:
    Point() { _x = 0; _y = 0; }
    Point(double x, double y) {  _x = mpf_class(x, PREC); _y = mpf_class(y, PREC); }
    mpf_class x() const {return _x;}
    mpf_class y() const {return _y;}
};

template <typename InputIterator>
class Polygon {
private:
    typedef std::vector<Point> Points;
    Points points;
public:
    typedef Points::iterator iterator;
    iterator begin() { return points.begin(); }
    iterator end() { return points.end(); }

    Polygon(InputIterator first, InputIterator last);
    bool contains( const Point q ) ;
};

}

template <typename InputIterator>
class K200644 {
public:
    typedef N200644::Point Point;
    typedef N200644::Polygon<InputIterator> Polygon;
};


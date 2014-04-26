#include <vector>

namespace N200644 {

class Point {
private:
    long double _x, _y;
public:
    Point() { _x = 0; _y = 0; }
    Point(double x, double y) { _x = x; _y = y; }
    long double x() const {return _x;}
    long double y() const {return _y;}
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
    bool contains( const Point& q ) const;
};

}

template <typename InputIterator>
class K200644 {
public:
    typedef N200644::Point Point;
    typedef N200644::Polygon<InputIterator> Polygon;
};


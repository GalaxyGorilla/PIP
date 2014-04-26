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

/* Check if a point is on the left (>0) or right (<0) side, based on the cross product.
 * The result is exactly 0 when q is part of the line spanned by head and tail */  
inline long double checkSide( const Point q, const Point head, const Point tail){
    return ( (head.x()-tail.x())*(q.y()-tail.y()) - (q.x()-tail.x())*(head.y()-tail.y()) );
}


} //namespace N200644

template <typename InputIterator>
class K200644 {
public:
    typedef N200644::Point Point;
    typedef N200644::Polygon<InputIterator> Polygon;
};


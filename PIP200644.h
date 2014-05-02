#include <vector>
#include <quadmath.h>

namespace N200644 {

class Point {
private:
    __float128 _x, _y;
public:
    Point() { _x = 0; _y = 0; }
    Point(double x, double y) { _x = x; _y = y; }
    __float128 x() const {return _x;}
    __float128 y() const {return _y;}
};

class Polygon {
private:
    typedef std::vector<Point> Points;
    Points points;
public:
    typedef Points::iterator iterator;
    iterator begin() { return points.begin(); }
    iterator end() { return points.end(); }

    template <typename InputIterator>
    Polygon(InputIterator first, InputIterator last);

    bool contains( const Point& q ) const;
};

/* polygon constructor */
template <typename InputIterator>
Polygon::Polygon(InputIterator first, InputIterator last){
    int size = std::distance(first, last) + 1;      //+1 for first element
    points.reserve(size);
    Point first_elem = *first;
    for(first; first!=last; ++first)
        points.push_back(*first);
    points.push_back(first_elem);
}

/* Check if a point is on the left (>0) or right (<0) side, based on the cross product.
 * The result is exactly 0 when q is part of the line spanned by head and tail */  
inline __float128 checkSide( const Point q, const Point head, const Point tail){
    return ( (head.x()-tail.x())*(q.y()-tail.y()) - (q.x()-tail.x())*(head.y()-tail.y()) );
}


} //namespace N200644

class K200644 {
public:
    typedef N200644::Point Point;
    typedef N200644::Polygon Polygon;
};


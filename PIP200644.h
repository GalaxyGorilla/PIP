#include <vector>
#include <gmpxx.h>

#define _200644_PREC 512

namespace N200644 {

class Point {
private:
    mpf_class _x, _y;
public:
    Point() { _x = 0; _y = 0; }
    Point(double x, double y) { _x = x; _y = y; }
    mpf_class getx() const {return _x;}
    mpf_class gety() const {return _y;}
    double x() const {return _x.get_d();}
    double y() const {return _y.get_d();}
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
    ~Polygon();

    bool contains( const Point& q ) const;
};

/* polygon constructor */
template <typename InputIterator>
Polygon::Polygon(InputIterator first, InputIterator last){
    mpf_set_default_prec (_200644_PREC);
    int size = std::distance(first, last) + 1;      //+1 for first element
    points.reserve(size);
    Point first_elem = *first;
    for(; first!=last; ++first)
        points.push_back(*first);
    points.push_back(first_elem);
}

/* Check if a point is on the left (>0) or right (<0) side, based on the cross product.
 * The result is exactly 0 when q is part of the line spanned by head and tail */  
inline mpf_class checkSide( const Point q, const Point head, const Point tail){
    return ( (head.getx()-tail.getx())*(q.gety()-tail.gety()) - (q.getx()-tail.getx())*(head.gety()-tail.gety()) );
}


} //namespace N200644

class K200644 {
public:
    typedef N200644::Point Point;
    typedef N200644::Polygon Polygon;
};


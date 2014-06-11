#include <vector>
#include <math.h>

namespace N200644 {

class Point {
private:
    double _x, _y;
public:
    Point() { _x = 0; _y = 0; }
    Point(double x, double y) { _x = x; _y = y; }
    double getx() const {return _x;}
    double gety() const {return _y;}
    double x() const {return _x;}
    double y() const {return _y;}
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

    double xmin, xmax;
    double ymin, ymax;
};

/* polygon constructor */
template <typename InputIterator>
Polygon::Polygon(InputIterator first, InputIterator last){
    int size = std::distance(first, last) + 1;      //+1 for first element
    points.reserve(size);
    Point first_elem = *first;
    xmin=first_elem.x(); xmax=first_elem.x();
    ymin=first_elem.y(); ymax=first_elem.y();
    for(; first!=last; ++first){
        points.push_back(*first);
        xmin = xmin>(*first).x() ? (*first).x() : xmin;
        xmax = xmax<(*first).x() ? (*first).x() : xmax;
        ymin = ymin>(*first).y() ? (*first).y() : ymin;
        ymax = ymax<(*first).y() ? (*first).y() : ymax;
    }
    points.push_back(first_elem);
}

/* Check if a point is on the left (>0) or right (<0) side, based on the cross product.
 * The result is exactly 0 when q is part of the line spanned by head and tail */  
inline double checkSide( const Point q, const Point head, const Point tail){
    double result = ( (head.getx()-tail.getx())*(q.gety()-tail.gety()) \
                    - (q.getx()-tail.getx())*(head.gety()-tail.gety()) );
    if( fabs(result) < 0.00001 ){
        long double qx = q.getx();
        long double qy = q.gety();
        long double headx = head.getx();
        long double heady = head.gety();
        long double tailx = tail.getx();
        long double taily = tail.gety();
        return ((headx-tailx)*(qy-taily) \
               - (qx-tailx)*(heady-taily) );
    }
    else
        return result;
}


} //namespace N200644

class K200644 {
public:
    typedef N200644::Point Point;
    typedef N200644::Polygon Polygon;
};


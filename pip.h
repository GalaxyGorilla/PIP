#include <vector>
#include <math.h> 

using namespace std;
namespace N200644 {

class Point {
private:
    double _x, _y;
public:
    Point() { _x = 0; _y = 0; }
    Point(double x, double y) { _x = x; _y = y; }
    double x() const {return _x;}
    double y() const {return _y;}
    Point normal() const;
    double len();
};

template <typename InputIterator>
class Polygon {
private:
    typedef vector<Point> Points;
    Points points;
public:
    typedef Points::iterator iterator;
    iterator begin() { return points.begin(); }
    iterator end() { return points.end(); }

    Polygon(InputIterator first, InputIterator last);
    bool contains( const Point q ) ;
    void print();
};

const Point operator+(Point const& lhs, Point const& rhs){
    Point result(lhs.x()+rhs.x(), lhs.y()+rhs.y());
    return result;
}
const Point operator-(Point const& lhs, Point const& rhs){
    Point result(lhs.x()-rhs.x(), lhs.y()-rhs.y());
    return result;
}
const double operator*(Point const& lhs, Point const& rhs){
    double result = (lhs.x() * rhs.x() + lhs.y() * rhs.y());
    return result;
}
const Point operator*(double const& lhs, Point const& rhs){
    Point result( lhs * rhs.x() ,  lhs * rhs.y());
    return result;
}
const bool operator==(Point const& lhs, Point const& rhs){
    if( lhs.x() - rhs.x() == 0 && lhs.y() - rhs.y() == 0 )
        return true;
    else
        return false;
}

}

template <typename InputIterator>
struct K200644 
{ 
    typedef N200644::Point Point;
    typedef N200644::Polygon<InputIterator> Polygon;
};


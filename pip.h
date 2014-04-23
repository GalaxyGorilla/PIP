#include <vector>
#include <math.h> 
#include <limits>

class Point {
private:
    double _x, _y;
public:
    Point(double x, double y) { _x = x; _y = y; }
    double x() const {return _x;}
    double y() const {return _y;}
    Point normal() const;
    double len();
};

class Polygon {
private:
    typedef std::vector<Point> Points;
    Points points;
public:
    typedef Points::iterator iterator;
    iterator begin() { return points.begin(); }
    iterator end() { return points.end(); }

    Polygon(iterator first, iterator last);
    bool contains( const Point q ) ;
    void print();
};

Polygon::Polygon(std::vector<Point>::iterator first, std::vector<Point>::iterator last){
    for(first; first != last; ++first)
        points.push_back(*first);
}

using namespace std;
void Polygon::print(){
    for(int i=0; i<points.size(); ++i)
        cout << "( " <<  points[i].x() << " , " << points[i].y() << " )\n";
}

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

double Point::len(){
    return sqrt(x() * x() + y() * y());
}

Point Point::normal() const{
    Point result(-y(), x());
    return (1/(result.len()))*result;
}

bool Polygon::contains( const Point q ){
    double rand_x = (double)rand()/(double)RAND_MAX;
    double rand_y = (double)rand()/(double)RAND_MAX;
    Point rand_normal(rand_x, rand_y); 
    Point dir = rand_normal.normal(); 
    rand_normal = (1/rand_normal.len()) * rand_normal ; 
    cout << "Normale: " << rand_normal.x() << " " << rand_normal.y() << endl;
    double rand_rhs = q * rand_normal;

    iterator _begin = ++begin();
    iterator _end = end();
    int counter = 0;
    for( _begin; _begin != _end; ++_begin){

        if ( q == *(_begin) ){
            return true;
        }

        Point diff = (*_begin - *(_begin-1));
        Point normal = diff.normal();
        double rhs = *_begin * normal;

        double divisor = rand_normal.x() * normal.y() - rand_normal.y() * normal.x();
        if (divisor == 0)
            continue;

        double x_div = rand_rhs * normal.y() - rand_normal.y() * rhs;
        double y_div = rand_normal.x() * rhs - rand_rhs * normal.x();
        if( x_div == 0 or y_div == 0 )
            continue;

        Point intersection(x_div/divisor, y_div/divisor);
        cout << "Schnitt: " << intersection.x() << " " << intersection.y() << endl;

        /* check if intersection is a vertex and fix the counter */
        if (intersection == *(_begin) ){
            Point pre = *(_begin-1) - *(_begin);
            Point succ = *(_begin+1) - *(_begin);
            if( (pre * rand_normal) * (succ * rand_normal) > 0)
                continue;
            else{
                ++counter;
                cout << "Counter: " << counter << endl;
                continue;
            }
        }

         /* First check if intersection is between the vertices (excluding the vertices) 
         * of the current edge, then check if intersection is on the 'upper' side of q.
         * If q is part of the edge (excluding te vertices) you have to check the direction
         * relative to the edge (does the direction go inside or outside the polygon?) */
        Point intersection_diff = intersection - *(_begin-1);
        double check_pos = (intersection_diff * diff) / diff.len();
        cout << "check_pos: " << check_pos << endl; 
        if( ( check_pos < diff.len() && ( check_pos > 0 ))
            && ( (intersection - q) * dir > 0 )){
            
            /* check if q is part of the edge */
            if (q == intersection){
                if ( diff.normal() * dir <= 0 )
                    ++counter;
                else;
                    continue;
            }
            else
                ++counter;
        }
        cout << "Counter: " << counter << endl;
        
    }
    
    if ( counter % 2 == 1 )
        return true;
    else
        return false;
}

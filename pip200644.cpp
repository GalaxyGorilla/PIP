#include "pip200644.h"

namespace N200644 {

/* polygon constructor */
template <typename InputIterator>
Polygon<InputIterator>::Polygon(InputIterator first, InputIterator last){
    int size = std::distance(first, last) + 1;      //+1 for first element
    points = std::vector<Point>(size);
    Point first_elem = *first;
    std::copy (first, last, points.begin());
    points[size-1] = first_elem;
}

/* Check if a point is on the left (>0) or right (<0) side, based on the cross product.
 * The result is exactly 0 when q is part of the line spanned head and tail */  
inline long double checkSide( const Point q, const Point head, const Point tail){
    return ( (head.x()-tail.x())*(q.y()-tail.y()) - (q.x()-tail.x())*(head.y()-tail.y()) );
}

/* The winding number algorithm */
template <typename InputIterator>
bool Polygon<InputIterator>::contains( const Point& q ) const {
    int size = points.size();
    int wn = 0;
    /* no vector iterators used here because of 'const' */
    for( int i=0; i < size; ++i ){

        /* case: upward egde -> increment winding number */
        if (points[i].y() <= q.y()) {
            if (points[i+1].y() > q.y())
                if ( checkSide(q, points[i], points[i+1]) > 0 )
                    ++wn;
        }

        /* case: downward egde -> decrement winding number */
        else { 
            if (points[i+1].y() <= q.y())
                if ( checkSide(q, points[i], points[i+1]) < 0 )
                    --wn;
        }

    }
    return ( wn != 0 );
}

}

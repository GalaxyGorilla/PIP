#include "pip200644.h"

namespace N200644 {

/* polygon constructor */
template <typename InputIterator>
Polygon<InputIterator>::Polygon(InputIterator first, InputIterator last){
    Point first_elem = *first;
    for(first; first != last; ++first)
        points.push_back(*first);
    points.push_back(first_elem);
}

/* Check if a point is on the left (>0) or right (<0) side, based on the cross product.
 * The result is exactly 0 when q is part of the line spanned head and tail */  
inline long double checkSide( const Point q, const Point head, const Point tail){
    return ( (head.x()-tail.x())*(q.y()-tail.y()) - (q.x()-tail.x())*(head.y()-tail.y()) );
}

/* The winding number algorithm */
template <typename InputIterator>
bool Polygon<InputIterator>::contains( const Point q ){
    iterator v = begin();
    iterator v_end = end();
    int wn = 0;
    for( v; v != v_end; ++v){

        /* case: upward egde -> increment winding number */
        if ((*v).y() <= q.y()) {
            if ((*(v+1)).y() > q.y())
                if ( checkSide(q, *v, *(v+1)) > 0 )
                    ++wn;
        }

        /* case: downward egde -> decrement winding number */
        else { 
            if ((*(v+1)).y() <= q.y())
                if ( checkSide(q, *v, *(v+1)) < 0 )
                    --wn;
        }

    }
    return ( wn != 0 );
}

}

#include "PIP200644.h"

namespace N200644 {

/* The winding number algorithm */
bool Polygon::contains( const Point& q ) const {
    int size = points.size() - 1;
    int wn = 0, i;
    /* line to the right */
    for( i=0; i < size; ++i ){
        /* case: upward egde -> increment winding number */
        if (points[i].gety() <= q.gety()) {
            if (points[i+1].gety() > q.gety()
                && checkSide(q, points[i], points[i+1]) > 0 )
                    ++wn;
        }
        /* case: downward egde -> decrement winding number */
        else if (points[i+1].gety() <= q.gety()
            && checkSide(q, points[i], points[i+1]) < 0 )
                --wn;
    }

    /* 
     * after the first iteration it is only possible to return a false negative result,
     * to avoid this the same procedure with other reference lines is repeated;
     * these reference lines should cover every possible special case 
     */

    if ( wn == 0 ) /* line to the left */
    for( i=0; i < size; ++i ){
        if (points[i].gety() >= q.gety()) {
            if (points[i+1].gety() < q.gety()
                && checkSide(q, points[i], points[i+1]) > 0 )
                ++wn;
        }
        else if (points[i+1].gety() >= q.gety()
            && checkSide(q, points[i], points[i+1]) < 0 )
            --wn;
    }
    if ( wn == 0 ) /* line downwards */
    for( i=0; i < size; ++i ){
        if (points[i].getx() <= q.getx()) {
            if (points[i+1].getx() > q.getx()
                && checkSide(q, points[i], points[i+1]) > 0 )
                    ++wn;
        }
        else if ( points[i+1].getx() <= q.getx()
            && checkSide(q, points[i], points[i+1]) < 0 )
            --wn;
    }
    if ( wn == 0 ) /* line upwards */
    for( i=0; i < size; ++i ){
        if (points[i].getx() >= q.getx()) {
            if (points[i+1].getx() < q.getx()
                && checkSide(q, points[i], points[i+1]) > 0 )
                ++wn;
        }
        else if (points[i+1].getx() >= q.getx()
            && checkSide(q, points[i], points[i+1]) < 0 )
            --wn;
    }

    return ( wn != 0 );

}

} // namespace N200644

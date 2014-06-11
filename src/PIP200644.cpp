#include "PIP200644.h"

namespace N200644 {

/* The winding number algorithm */
bool Polygon::contains( const Point& q ) const {

    /* bounding box */
    if (q.getx() < xmin
        || q.getx() > xmax
        || q.gety() < ymin
        || q.gety() > ymax)
        return 0;

    int size = points.size() - 1;
    int wn = 0, i;
    /* line to the right */
    for( i=0; i < size; ++i ){
        if( points[i].getx() == q.getx()
            && points[i].gety() == q.gety() )
            return 1;
        
        /* case: upward egde -> increment winding number */
        if( points[i].gety() <= q.gety() ){
            if( points[i+1].gety() > q.gety() ){
                if( checkSide(q, points[i], points[i+1]) > 0 )
                ++wn;
            }
        }
        /* case: downward egde -> decrement winding number */
        else if( points[i+1].gety() <= q.gety() ){
            if( checkSide(q, points[i], points[i+1]) < 0 )
            --wn;
        }
    }

    /* 
     * after the first iteration it is only possible to return a false negative result,
     * to avoid this the same procedure with other reference lines is repeated;
     */

    if ( wn == 0 ) /* line to the left */
    for( i=0; i < size; ++i ){
        if( points[i].gety() >= q.gety() ){
            if( points[i+1].gety() < q.gety() ){
                if( checkSide(q, points[i], points[i+1]) > 0 )
                ++wn;
            }
        }
        else if( points[i+1].gety() >= q.gety() ){
            if( checkSide(q, points[i], points[i+1]) < 0 )
            --wn;
        }
    }

    return ( wn != 0 );

}

} // namespace N200644

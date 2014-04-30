#include "PIP200644.h"

namespace N200644 {

/* The winding number algorithm */
bool Polygon::contains( const Point& q ) const {
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

    if ( wn == 0 ){
        for( int i=0; i < size; ++i ){

            /* case: upward egde -> increment winding number */
            if (points[i].x() <= q.x()) {
                if (points[i+1].x() > q.x())
                    if ( checkSide(q, points[i], points[i+1]) > 0 )
                        ++wn;
            }

            /* case: downward egde -> decrement winding number */
            else { 
                if (points[i+1].x() <= q.x())
                    if ( checkSide(q, points[i], points[i+1]) < 0 )
                        --wn;
            }

        }

    }

    return ( wn != 0 );

}

}

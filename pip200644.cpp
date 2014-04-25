#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <gmpxx.h>
#include "pip200644.h"

namespace N200644 {

template <typename InputIterator>
Polygon<InputIterator>::Polygon(InputIterator first, InputIterator last){
    Point first_elem = *first;
    for(first; first != last; ++first)
        points.push_back(*first);
    points.push_back(first_elem);
}

inline long double checkSide( const Point q, const Point head, const Point tail){
    return ( (head.x()-tail.x())*(q.y()-tail.y()) - (q.x()-tail.x())*(head.y()-tail.y()) );
}

template <typename InputIterator>
bool Polygon<InputIterator>::contains( const Point q ){
    iterator v = begin();
    iterator _end = end();
    int wn = 0;
    for( v; v != _end; ++v){

        /* upward egde */
        if ((*v).y() <= q.y()) {
            if ((*(v+1)).y() > q.y())
                if ( checkSide(q, *v, *(v+1)) < 0 )
                    ++wn;
        }

        /* downward edge */
        else { 
            if ((*(v+1)).y() <= q.y())
                if ( checkSide(q, *v, *(v+1)) > 0 )
                    --wn;
        }

    }
    return ( wn != 0 );
}

}

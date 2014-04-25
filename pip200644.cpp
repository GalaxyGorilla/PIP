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

inline double checkSide( const Point q, const Point head, const Point tail){
    return ( (head.x()-tail.x())*(q.y()-tail.y()) - (q.x()-tail.x())*(head.y()-tail.y()) );
}

template <typename InputIterator>
bool Polygon<InputIterator>::contains( const Point q ){
    iterator v = begin();
    iterator _end = end();
    int c = 0;
    for ( v; v != _end; ++v){
        Point v0 = *v;
        Point v1 = *(v+1);
        if ( ((v1.y() > q.y()) != (v0.y()>q.y())) 
            && (q.x() < (v0.x()-v1.x()) * (q.y()-v1.y()) / (v0.y()-v1.y()) + v1.x()) )
            c = !c;
    }
    return c;
}

}

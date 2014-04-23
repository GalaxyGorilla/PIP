#include <iostream>
#include <vector>
#include <stdlib.h> 
#include "pip200644.h"

namespace N200644 {

template <typename InputIterator>
Polygon<InputIterator>::Polygon(InputIterator first, InputIterator last){
    Point first_elem = *first;
    for(first; first != last; ++first)
        points.push_back(*first);
    points.push_back(first_elem);
}

template <typename InputIterator>
void Polygon<InputIterator>::print(){
    for(int i=0; i<points.size(); ++i)
        std::cout << "( " <<  points[i].x() << " , " << points[i].y() << " )\n";
}

double Point::len(){
    return sqrt(x() * x() + y() * y());
}

Point Point::normal() const{
    Point result(-y(), x());
    return (1/(result.len()))*result;
}

template <typename InputIterator>
bool Polygon<InputIterator>::contains( const Point q ){
    double rand_x = (double)rand()/(double)RAND_MAX;
    double rand_y = (double)rand()/(double)RAND_MAX;
    Point rand_normal(rand_x, rand_y); 
    Point dir = rand_normal.normal(); 
    rand_normal = (1/rand_normal.len()) * rand_normal ; 
    //cout << "Normale: " << rand_normal.x() << " " << rand_normal.y() << endl;
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
       // cout << "Schnitt: " << intersection.x() << " " << intersection.y() << endl;

        /* check if intersection is a vertex and fix the counter */
        if (intersection == *(_begin) ){
            Point pre = *(_begin-1) - *(_begin);
            Point succ = *(_begin+1) - *(_begin);
            if( (pre * rand_normal) * (succ * rand_normal) > 0)
                continue;
            else{
                ++counter;
                //cout << "Counter: " << counter << endl;
                continue;
            }
        }

         /* First check if intersection is between the vertices (excluding the vertices) 
         * of the current edge, then check if intersection is on the 'upper' side of q.
         * If q is part of the edge (excluding te vertices) you have to check the direction
         * relative to the edge (does the direction go inside or outside the polygon?) */
        Point intersection_diff = intersection - *(_begin-1);
        double check_pos = (intersection_diff * diff) / diff.len();
        //cout << "check_pos: " << check_pos << endl; 
        if( ( check_pos < diff.len() && ( check_pos > 0 ))
            && ( (intersection - q) * dir > 0 )){
            
            /* check if q is part of the edge */
            if (q == intersection){
                /* if yes check the direction vector */
                if ( diff.normal() * dir <= 0 )
                    ++counter;
                else;
                    continue;
            }
            else
                ++counter;
        }
        //cout << "Counter: " << counter << endl;
        
    }
    
    if ( counter % 2 == 1 )
        return true;
    else
        return false;
}

}

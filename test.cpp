#include <iostream>
#include <vector>
#include <stdlib.h> 
#include "pip.cpp"

int main(int argc, char* argv[]) { 

   double x = atof(argv[1]);
   double y = atof(argv[2]);
   Point point(x,y);

   std::vector<Point> myvector;
   myvector.push_back(Point(0.1,0.1));
   myvector.push_back(Point(0.2,0.9));
   myvector.push_back(Point(0.8,0.4));
   myvector.push_back(Point(0.1,0.1));

   Polygon<std::vector<Point>::iterator> P(myvector.begin(), myvector.end());

   Polygon<std::vector<Point>::iterator>::iterator iter = P.begin();

   P.print();
   std::cout << P.contains(point) << std::endl;

   return 0;
       
}

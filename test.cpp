#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <sstream>
#include <string>
#include <fstream>
#include "pip200644.cpp"

using namespace std;

int main(int argc, char* argv[]) { 

    for (int i=1; i<4; i++){

        ostringstream case_polygon;
        ostringstream case_querypoints;
        ostringstream case_locations;
        case_polygon << i << "_polygon.txt";
        case_querypoints << i << "_querypoints.txt";
        case_locations << i << "_locations.txt";

        ifstream infile_polygon(case_polygon.str().c_str());
        ifstream infile_querypoints(case_querypoints.str().c_str());
        ifstream infile_locations(case_locations.str().c_str());

        vector<N200644::Point> read_polygon;
        double x1, y1;
        while (infile_polygon >> x1 >> y1){
            N200644::Point point(x1,y1);
            read_polygon.push_back(point);
        }

        vector<N200644::Point> read_querypoints;
        double x2, y2;
        while (infile_querypoints >> x2 >> y2){
            N200644::Point point(x2,y2);
            read_querypoints.push_back(point);
        }

        vector<int> read_locations;
        int result;
        while (infile_locations >> result){
            read_locations.push_back(result);
        }

        K200644<vector<N200644::Point>::iterator>::Polygon P(read_polygon.begin(), read_polygon.end());

        vector<N200644::Point>::iterator query_iter = read_querypoints.begin();
        vector<int>::iterator locations_iter = read_locations.begin();
        int counter = 0;
        for( query_iter ; query_iter != read_querypoints.end() ; ++query_iter ){
            if (P.contains( *query_iter ) == *locations_iter)    
                ++counter;
            ++locations_iter;
        }

        cout << "Ergebnis: " << counter << " von " << read_querypoints.size() << endl;

    }

    return 0;
       
}

#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include "PIP200644.h"

#define PLOTTING 1
#define N_TESTCASES 6

#define PRINT_BUFFER(buffer,point) buffer << (*point).x() << " " << (*point).y() << endl; 

using namespace std;

int main(int argc, char *argv[]) { 
    
    int case_index = N_TESTCASES;
    int start_case = 1;
    if (argc == 2){
        case_index = atoi(argv[1]);
        start_case = case_index;
    }

    cout.precision(4);
    ofstream positive;
    ofstream negative;
    ofstream ok;
    ofstream polygonfile;
    positive.open("./plotting/positive.txt");
    negative.open("./plotting/negative.txt");
    ok.open("./plotting/ok.txt");
    polygonfile.open("./plotting/polygon.txt");

    for (int i=start_case; i<=case_index; i++){

        ostringstream case_polygon;
        ostringstream case_querypoints;
        ostringstream case_locations;
        case_polygon << "testcases/" << i << "_polygon.txt";
        case_querypoints << "testcases/" << i << "_querypoints.txt";
        case_locations << "testcases/" << i << "_locations.txt";

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

        vector<bool> read_locations;
        bool loc_result;
        while (infile_locations >> loc_result){
            read_locations.push_back(loc_result);
        }

        K200644::Polygon P(read_polygon.begin(), read_polygon.end());
        K200644::Polygon::iterator first = P.begin();
        K200644::Polygon::iterator last = P.end();
        for(; first!=last; ++first)
            PRINT_BUFFER(polygonfile, first)

        vector<N200644::Point>::iterator query_iter = read_querypoints.begin();
        vector<bool>::iterator locations_iter = read_locations.begin();
        int counter = 0;
        bool result;
        clock_t start = clock();
        for( ; query_iter != read_querypoints.end() ; ++query_iter, ++locations_iter ){

            result = P.contains(*query_iter);
            if (result == *locations_iter)
                ++counter;

            if(PLOTTING){
                if (result != *locations_iter && result) 
                    PRINT_BUFFER(positive, query_iter)
                else if(result != *locations_iter && !result) 
                    PRINT_BUFFER(negative, query_iter)
                else 
                    PRINT_BUFFER(ok, query_iter)
            }


        }
        clock_t ends = clock();

        cout << i << ". " << counter << " / " << read_querypoints.size() << " ["    \
            << ((double)counter)/read_querypoints.size() * 100 << "%]"              \
            << " in " << (double) (ends - start) / CLOCKS_PER_SEC << "s" << endl;

    }

    return 0;

}

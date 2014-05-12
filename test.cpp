#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include "PIP200644.cpp"

using namespace std;

int main(int argc, char* argv[]) { 

    cout.precision(4);
    ofstream positive;
    ofstream negative;
    ofstream wrong;
    positive.open("positive.txt");
    negative.open("negative.txt");
    wrong.open("wrong.txt");

    int prec = 20;
    int width = 46;
    char bufx[128];
    char bufy[128];

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

        vector<bool> read_locations;
        bool result;
        while (infile_locations >> result){
            read_locations.push_back(result);
        }

        K200644::Polygon P(read_polygon.begin(), read_polygon.end());

        vector<N200644::Point>::iterator query_iter = read_querypoints.begin();
        vector<bool>::iterator locations_iter = read_locations.begin();
        int counter = 0;
        clock_t start = clock();
        for( query_iter ; query_iter != read_querypoints.end() ; ++query_iter, ++locations_iter ){

            //quadmath_snprintf (bufx, sizeof bufx, "%+-#*.20Qe", width, (*query_iter).x());
            //quadmath_snprintf (bufy, sizeof bufy, "%+-#*.20Qe", width, (*query_iter).y());

            bool result = P.contains(*query_iter);
            if (result == *locations_iter)
                ++counter;
            //else
            //    wrong << string(bufx) << " " << string(bufy) << endl;

            //if( result )
            //    positive << string(bufx) << " " << string(bufy) << endl;
            //else
            //    negative << string(bufx) << " " << string(bufy) << endl;

        }
        clock_t ends = clock();

        cout << "Result: " << counter << " / " << read_querypoints.size() << " [" << ((double)counter)/read_querypoints.size() * 100 << "%]" \
            << " in " << (double) (ends - start) / CLOCKS_PER_SEC << " secs" << endl;

    }

    return 0;

}

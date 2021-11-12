
#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include "fstream"
#include "iostream"
#include "vector"
using namespace std;

class TimeSeries{
    vector<string> faetures;
    vector<vector<string>> data;
public:
    TimeSeries(const char* CSVfileName);


};




#endif /* TIMESERIES_H_ */

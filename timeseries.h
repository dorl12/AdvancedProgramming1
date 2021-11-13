

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include "fstream"
#include "iostream"
#include "vector"
using namespace std;

class TimeSeries{
    vector<string> features;
    vector<vector<string>> dataList;
public:
    TimeSeries(const char* CSVfileName);
    void initializeFeatures(ifstream file);
    void initializeDataList(ifstream file);
};

#endif /* TIMESERIES_H_ */

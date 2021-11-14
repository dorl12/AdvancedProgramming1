

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class TimeSeries{
    vector<string> features;
    vector<vector<float>> dataList;
public:
    TimeSeries(const char* CSVfileName);
    void initializeFeatures(fstream &file);
    void initializeDataList(fstream &file);
};

#endif /* TIMESERIES_H_ */

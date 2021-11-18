/*
 * timeseries.h
 *
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include "fstream"
#include "iostream"
#include "vector"
#include "anomaly_detection_util.h"
using namespace std;

class TimeSeries{
    vector<string> features;
    vector<vector<float>> dataList;
public:
    TimeSeries(const char* CSVfileName);
    void initializeFeatures(fstream &file);
    void initializeDataList(fstream &file);
    vector<vector<float>> getDataList() const;
    int numOfFeatures()const;
    float* vecToArray(int index) const;
    string getFeature(int index) const;
    vector<string> getFeaturesVec() const;
    Point** vecToPoints(int f1, int f2) const;
    int numOfRows() const;
    float maxDev(Point** points, Line line, int size) const;
    int getIndexFeature(vector<string> v, string s) const;
};

#endif /* TIMESERIES_H_ */


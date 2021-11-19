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

// a class to define a time series object
class TimeSeries{
    vector<string> features;
    vector<vector<float>> dataList;
public:
    // the constructor of the class TimeSeries
    TimeSeries(const char* CSVfileName);
    // initializes a vector of the features
    void initializeFeatures(fstream &file);
    // initializes a vector of vectors of the data list
    void initializeDataList(fstream &file);
    // returns the data list
    vector<vector<float>> getDataList() const;
    // returns the number of features
    int numOfFeatures()const;
    // returns an array of a specific vector from the data list
    float* vecToArray(int index) const;
    // returns the name of a feature from the features vector according to the index
    string getFeature(int index) const;
    // returns the features vector
    vector<string> getFeaturesVec() const;
    // returns an array of pointers to points from the data list according to given features
    Point** vecToPoints(int f1, int f2) const;
    // returns the num of rows in the data list
    int numOfRows() const;
    // returns the maximal deviation between the points in the array and the line equation of the points
    float maxDev(Point** points, Line line, int size) const;
    // returns the index of the feature in the vector of the features according to its name
    int getIndexFeature(vector<string> v, string s) const;
};

#endif /* TIMESERIES_H_ */
/*
 * timeseries.cpp
 *
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */
#include <sstream>
#include "timeseries.h"

// the constructor of the class TimeSeries
TimeSeries::TimeSeries(const char *CSVfileName) {
    fstream file(CSVfileName);
    initializeFeatures(file);
    initializeDataList(file);
    file.close();
}

// initializes a vector of the features
void TimeSeries::initializeFeatures(fstream &file) {
    string firstLine;
    // getting the first line of the file
    getline(file, firstLine);
    // using string stream in order to parse the line into features
    stringstream ss(firstLine);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        this->features.push_back(substr);
    }
}

// initializes a vector of vectors of the data list
void TimeSeries::initializeDataList(fstream &file) {
    vector<vector<float>> dataListPer(this->features.size(), vector<float>());
    string line;
    // parse each line and push each value to the right vector according to the order
    while (getline(file, line)) {
        stringstream ss(line);
        for (int i = 0; i < features.size();) {
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                // using stof in order to convert string into float
                dataListPer[i].push_back(stof(substr));
                i++;
            }
        }
        this->dataList = dataListPer;
    }
}

// returns the data list
vector<vector<float>> TimeSeries::getDataList() const{
    return dataList;
}

// returns the number of features
int TimeSeries::numOfFeatures()const{
    return features.size();
}

// returns an array of a specific vector from the data list
float* TimeSeries::vecToArray(int index) const{
    vector<float> cur = dataList[index];
    int size = (int)cur.size();
    float* arr;
    arr = new float[size];
    for(int i = 0; i < size; i++) {
        arr[i] = dataList[index][i];
    }
    return arr;
}

// returns the name of a feature from the features vector according to the index
string TimeSeries::getFeature(int index) const {
    return features[index];
}

// returns the features vector
vector<string> TimeSeries::getFeaturesVec() const {
    return features;
}

// returns an array of pointers to points from the data list according to given features
Point** TimeSeries::vecToPoints(int f1, int f2) const {
    int size = dataList[f1].size();
    // initializing an array of pointers to points
    Point** arr;
    arr = new Point*[size];
    // create a point according to the features and add it to the array
    for(int i =0; i < size; i++) {
        float  x = dataList[f1][i];
        float y = dataList[f2][i];
        Point* p = new Point(x, y);
        arr[i] = p;
    }
    return arr;
}

// returns the num of rows in the data list
int TimeSeries::numOfRows() const{
    return dataList[0].size();
}

// returns the maximal deviation between the points in the array and the line equation of the points
float TimeSeries::maxDev(Point** arrP, Line line, int size) const {
    float maximalDev = 0, temp;
    // iterating through the array of pointers to points and calculating the maximal deviation
    for (int i = 0; i < size; i++) {
        Point* point = arrP[i];
        temp = dev(*point, line);
        if (temp > maximalDev) {
            maximalDev = temp;
        }
    }
    return maximalDev;
}

// returns the index of the feature in the vector of the features according to its name
int TimeSeries::getIndexFeature(vector<string> v, string s)const {
    for (int i = 0; i < v.size(); i ++) {
        if (!v[i].compare(s)) {
            return i;
        }
    }
    return -1;
}
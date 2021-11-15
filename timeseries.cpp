
#include <sstream>
#include "timeseries.h"
using namespace std;

TimeSeries::TimeSeries(const char* CSVfileName) {
    fstream file(CSVfileName);
    initializeFeatures(file);
    initializeDataList(file);
    file.close();
}

void TimeSeries::initializeFeatures(fstream &file) {
    string firstLine = "";
    getline(file,firstLine);
    stringstream ss(firstLine);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        features.push_back(substr);
    }
}

void TimeSeries::initializeDataList(fstream &file) {
    string line = "";
    while (getline(file,line)) {
        stringstream ss(line);
        for (int i = 0; i < features.size();) {
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                dataList[i].push_back(stof(substr));
                i++;
            }
        }
    }
}

vector<vector<float>> TimeSeries::getDataList()const{
    return dataList;
}
int TimeSeries::numOfFeatures()const{
    return features.size();
}
float* TimeSeries::vecToArray(int index) const{
    int size = dataList[index].size();
    float arr[size];
    for(int i = 0; i < size; i++) {
        arr[i] = dataList[index][i];
    }
    return arr;
}
string TimeSeries::getFeature(int index) const {
    return features[index];
}
vector<string> TimeSeries::getFeaturesVec() const {
    return features;
}
Point** TimeSeries::vecToPoints(int f1, int f2) const {
    int size = dataList[f1].size();
    Point* arr[size];
    for(int i =0; i < size; i++) {
        float  x = dataList[f1][i];
        float y = dataList[f2][i];
        Point* p = new Point(x, y);
        arr[i] = p;
    }
    return arr;
}

int TimeSeries::numOfRows() const{
    return dataList[0].size();
}
float TimeSeries::maxDev(Point** arrP, Line line, int size) const {
    float maximalDev = 0, temp;
    for (int i = 0; i < size; i++) {
        Point* point = arrP[i];
        temp = dev(*point, line);
        if (temp > maximalDev) {
            maximalDev = temp;
        }
    }
    return maximalDev;
}
int TimeSeries::getIndexFeature(vector<string> v, string s)const {
    for (int i = 0; i < v.size(); i ++) {
        if (v[i].compare(s) == 0) {
            return i;
        }
    }
    return -1;
}


//write a func that return max dev (get line, get points**, size)
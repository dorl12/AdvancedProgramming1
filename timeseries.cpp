#include <sstream>
#include "timeseries.h"

TimeSeries::TimeSeries(const char* CSVfileName) {
    ifstream file(CSVfileName);
    initializeFeatures(file);
    initializeDataList(file);
    file.close();
}

void TimeSeries::initializeFeatures(ifstream file) {
    string firstLine = "";
    getline(file,firstLine);
    stringstream ss(firstLine);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        features.push_back(substr);
    }
}

void TimeSeries::initializeDataList(ifstream file) {
    string line = "";
    while (getline(file,line)) {
        stringstream ss(line);
        for (int i = 0; i < features.size();) {
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                dataList[i].push_back(substr);
                i++;
            }
        }
    }
}

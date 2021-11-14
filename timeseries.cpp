#include <sstream>
#include "timeseries.h"

TimeSeries::TimeSeries(const char *CSVfileName) {
    fstream file(CSVfileName);
    initializeFeatures(file);
    initializeDataList(file);
    file.close();
}

void TimeSeries::initializeFeatures(fstream &file) {
    string firstLine;
    getline(file, firstLine);
    stringstream ss(firstLine);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        this->features.push_back(substr);
    }
}

void TimeSeries::initializeDataList(fstream &file) {
    vector<vector<float>> dataListPer(this->features.size(),vector<float>());
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        for (int i = 0; i < this->features.size();) {
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                dataListPer[i].push_back(stof(substr));
                i++;
            }
        }
    }
    this->dataList = dataListPer;
}

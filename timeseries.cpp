#include "timeseries.h"

TimeSeries::TimeSeries(const char* CSVfileName) {
    ifstream myFile;
    myFile.open(CSVfileName);
    while(myFile.good()) {
        string firstLine;
        getline(myFile, firstLine);
        firstLine.


}

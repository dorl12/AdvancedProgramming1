/*
 * AnomalyDetector.h
 *
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */
#ifndef ANOMALYDETECTOR_H_
#define ANOMALYDETECTOR_H_

#include <string>
#include <vector>
#include "timeseries.h"
#include "math.h"
using namespace std;

// the class AnomalyReport defines an anomaly report using a description and a time step methods.
class AnomalyReport{
public:
    const string description;
    const long timeStep;
    // the constructor of the class AnomalyReport
    AnomalyReport(string description, long timeStep):description(description),timeStep(timeStep){}
};

/*
    the class TimeSeriesAnomalyDetector defines an interface
    that describes the general functionality of every anomaly detector
*/
class TimeSeriesAnomalyDetector {
public:
    // implementation of the preliminary stage of anomaly detecting
    virtual void learnNormal(const TimeSeries& ts)=0;
    // given a TimeSeries object, returns a list of reports
    virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    // the destructor of the class TimeSeriesAnomalyDetector
    virtual ~TimeSeriesAnomalyDetector(){}
};

#endif /* ANOMALYDETECTOR_H_ */
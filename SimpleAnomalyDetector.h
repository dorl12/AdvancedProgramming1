/*
 * SimpleAnomalyDetector.h
 *
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */
#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

// a struct that defines a correlated features
struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};

// a class to define a detector of simple anomaly
class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    vector<correlatedFeatures> cf;
public:
    // the constructor of the class SimpleAnomalyDetector
    SimpleAnomalyDetector();
    // the destructor of the class SimpleAnomalyDetector
    virtual ~SimpleAnomalyDetector();

    /*
        examines for each feature which of the other features is the most correlative
        To him according to pearson function
    */
    virtual void learnNormal(const TimeSeries& ts);
    // returns a vector of anomaly reports according to anomalies found in comparison to the learning phase
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    // returns a vector of correlated features
    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
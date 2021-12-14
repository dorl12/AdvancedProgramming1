

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();

    virtual void learnDetectCombined(const TimeSeries &ts, float m, int featureIndex1, int featureIndex2);

    virtual bool isAnomalous(float x, float y, correlatedFeatures featureCouple);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
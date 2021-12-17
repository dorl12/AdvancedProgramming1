
#include "HybridAnomalyDetector.h"
#include "minCircle.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::learnDetectCombined(const TimeSeries &ts, float m, int featureIndex1, int featureIndex2) {
    // detect for simple detector
    SimpleAnomalyDetector::learnDetectCombined(ts, m, featureIndex1, featureIndex2);
    // generate minimum enclosing circle
    if (m > 0.5 && m < threshold) {
        Circle circle = findMinCircle(ts.vecToPoints(featureIndex1, featureIndex2), ts.numOfRows());
        correlatedFeatures featureCouple;
        featureCouple.feature1 = ts.getFeature(featureIndex1);
        featureCouple.feature2 = ts.getFeature(featureIndex2);
        featureCouple.lin_reg = linear_reg(ts.vecToPoints
                (featureIndex1, featureIndex2), ts.numOfRows());
        featureCouple.corrlation = m;
        featureCouple.threshold = circle.radius * 1.1;
        featureCouple.cx = circle.center.x;
        featureCouple.cy = circle.center.y;
        cf.push_back(featureCouple);
    }
}

bool HybridAnomalyDetector::isAnomalous(float x, float y, correlatedFeatures featureCouple) {
    // run the simple detector
    if (SimpleAnomalyDetector::isAnomalous(x, y, featureCouple)) {
        return true;
    }
    // generate minimum enclosing circle
    else if((featureCouple.corrlation > 0.5 && featureCouple.corrlation < threshold &&
             eucDist(Point(featureCouple.cx,featureCouple.cy), Point(x, y)) > featureCouple.threshold)) {
        return true;
    }
    else {
        return false;
    }
}

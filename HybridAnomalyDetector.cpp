
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::learnDetectCombined(const TimeSeries &ts, float m, int featureIndex1, int featureIndex2) {
    SimpleAnomalyDetector::learnDetectCombined(ts, m, featureIndex1, featureIndex2);
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
    return (featureCouple.corrlation >= threshold && SimpleAnomalyDetector::isAnomalous(x, y, featureCouple)) ||
            (featureCouple.corrlation > 0.5 && featureCouple.corrlation < threshold && eucDist(Point(featureCouple.cx
            ,featureCouple.cy), Point(x, y)) > featureCouple.threshold);
}

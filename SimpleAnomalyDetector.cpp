#include "anomaly_detection_util.h"
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    correlatedFeatures featureCouple;
    float m = 0.9, c, p;
    for(int i = 0; i < ts.numOfFeatures(); i++) {
        m = 0;
        c = -1;
        for (int j = i+1; j < ts.numOfFeatures(); j++) {
            p = abs(pearson(ts.vecToArray(i),ts.vecToArray(j) , ts.getDataList().size()));
            if(p > m) {
                m = p;
                c = j;
            }
        }
        if (c != -1) {
            featureCouple.feature1 = ts.getFeature(i);
            featureCouple.feature2 = ts.getFeature(c);
            featureCouple.lin_reg = linear_reg(ts.vecToPoints(i, c), ts.numOfRows());
            featureCouple.corrlation = p;
            featureCouple.threshold = ts.maxDev(ts.vecToPoints(i,c), featureCouple.lin_reg, ts.numOfRows());
            this->cf.push_back(featureCouple);
            //delete arr of points
        }
    }
    // TODO Auto-generated destructor stub
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    // two loops
    // 1st loop run on corlated features
    // check for each row
    // לעבור על כל השורות בTS. יוצרים נקודה
    // return vector of anomaly report
    // TODO Auto-generated destructor stub
}


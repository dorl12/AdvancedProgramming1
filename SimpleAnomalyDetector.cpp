/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */
#include "anomaly_detection_util.h"
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

/*
 * function implemented like the pseudocode in assignment
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    correlatedFeatures featureCouple;
    float m = 0.9, c, p;
    for(int i = 0; i < ts.numOfFeatures(); i++) {
        m = 0.9;
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
            featureCouple.corrlation = m;
            featureCouple.threshold = (float)(ts.maxDev(ts.vecToPoints(i,c),
                                                        featureCouple.lin_reg, ts.numOfRows()) * 1.1);
            this->cf.push_back(featureCouple);
            //optional implement - delete arr of points
        }

    }
    // TODO Auto-generated destructor stub
}
/*
 * by given correlated feature with two features,
 * looping row by row to detect bigger anomaly(indicator holds it).
 * if an anomaly was detected, indicator > threshold,
 * we will push object from type "anomaly report" to the vector vAP that is holding all
 * anomaly reports.
 *
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> vAP;
    vector<correlatedFeatures>::iterator iter;
    float threshold, indicator, x, y;
    int index_f1, index_f2;

    for (iter = cf.begin(); iter < cf.end(); iter++) {
        index_f1 = ts.getIndexFeature(ts.getFeaturesVec(), iter->feature1);
        index_f2 = ts.getIndexFeature(ts.getFeaturesVec(), iter->feature2);
        threshold = iter->threshold;
        for (int i = 0; i < ts.numOfRows(); i ++) {
            x = ts.getDataList()[index_f1][i];
            y = ts.getDataList()[index_f2][i];
            indicator = dev(Point(x,y), iter->lin_reg);
            if (indicator > threshold) {
                // concatenating string. exapmle : "A-C"
                string s = iter->feature1;
                s.append("-");
                s.append(iter->feature2);
                // i+1 because the vector start with index 0;
                AnomalyReport* ap = new AnomalyReport(s, i+1);
                vAP.push_back(*ap);
            }
        }
    }
    return vAP;
    // TODO Auto-generated destructor stub
}

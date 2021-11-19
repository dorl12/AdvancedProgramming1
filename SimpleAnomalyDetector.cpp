/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */
#include "anomaly_detection_util.h"
#include "SimpleAnomalyDetector.h"

// the constructor of the class SimpleAnomalyDetector
SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub
}

// the destructor of the class SimpleAnomalyDetector
SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

/*
   examines for each feature which of the other features is the most correlative
   To him according to pearson function
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    correlatedFeatures featureCouple;
    float m , c, p;
    for(int i = 0; i < ts.numOfFeatures(); i++) {
        // a threshold that features above it will be considered correlative
        m = 0.9;
        c = -1;
        /*
            for each feature we will measure using Pearson the correlation between the value vector of
            𝑓𝑖 and the vector of values of each 𝑓𝑗≠𝑖
         */
        for (int j = i+1; j < ts.numOfFeatures(); j++) {
            p = abs(pearson(ts.vecToArray(i),ts.vecToArray(j) , ts.getDataList().size()));
            if(p > m) {
                m = p;
                c = j;
            }
        }
        /*
            for each feature 𝑓𝑖 we return the feature 𝑓𝑗 for which we obtained the result of
            Pearson at the absolute highest value
         */
        if (c != -1) {
            featureCouple.feature1 = ts.getFeature(i);
            featureCouple.feature2 = ts.getFeature(c);
            featureCouple.lin_reg = linear_reg(ts.vecToPoints(i, c), ts.numOfRows());
            featureCouple.corrlation = m;
            featureCouple.threshold = (float)(ts.maxDev(ts.vecToPoints(i,c),
                                                        featureCouple.lin_reg, ts.numOfRows()) * 1.1);
            this->cf.push_back(featureCouple);
        }
        // optional implement - delete vecToArray and vecToPoints
    }
}

// returns a vector of anomaly reports according to anomalies found in comparison to the learning phase
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> vAP;
    vector<correlatedFeatures>::iterator iter;
    float threshold, indicator, x, y;
    int index_f1, index_f2;
    // for each two-dimensional point, we will measure its distance from the regression line
    for (iter = cf.begin(); iter < cf.end(); iter++) {
        index_f1 = ts.getIndexFeature(ts.getFeaturesVec(), iter->feature1);
        index_f2 = ts.getIndexFeature(ts.getFeaturesVec(), iter->feature2);
        threshold = iter->threshold;
        for (int i = 0; i < ts.numOfRows(); i ++) {
            x = ts.getDataList()[index_f1][i];
            y = ts.getDataList()[index_f2][i];
            indicator = dev(Point(x,y), iter->lin_reg);
            /*
                in case the distance is greater than the maximal distance we found for these features
                in the learning phase, we will include in the report the features involved
             */
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
    // return the vector of anomaly reports
    return vAP;
}
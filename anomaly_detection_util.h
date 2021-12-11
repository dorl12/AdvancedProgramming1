/*
 * anomaly_detection_util.h
 *
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */
#ifndef ANOMALYDETECTORUTIL_H_
#define ANOMALYDETECTORUTIL_H_

// returns the average of X
float avg(float* x, int size);

// returns the variance of the elements of X
float var(float* x, int size);

// returns the covariance of X and Y
float cov(float* x,  float* y, int size);

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size);

// the class Line describes a line
class Line{
public:
    float a,b;
    Line():a(0),b(0){}
    Line(float a, float b):a(a),b(b){}
    float f(float x){
        return a*x+b;
    }
};

// the class Point describes a point
class Point{
public:
    float x,y;
    Point() :x(0), y(0){}
    Point(float x, float y):x(x),y(y){}
};

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size);

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size);

// returns the deviation between point p and the line
float dev(Point p,Line l);

#endif
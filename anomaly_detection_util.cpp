/*
 * anomaly_detection_util.cpp
 *
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */
#include <stdexcept>
#include <math.h>
#include "anomaly_detection_util.h"

// returns the average of X
float avg(float* x, int size){
    if (size == 0){
        throw std::runtime_error("Size Not Valid");
    }
    float sum = 0;
    float average;
    for(int i = 0; i < size;i++){
        sum += x[i];
    }
    average = sum / (float)size;
    return average;
}

// returns the variance of the elements of X
float var(float* x, int size){
    if (size == 0){
        throw std::runtime_error("Size Not Valid");
    }
    float sqDiff = 0;
    float mean = avg(x, size);
    for (int i = 0; i < size; i++) {
        sqDiff += (x[i] - mean) * (x[i] - mean);
    }
    return sqDiff / (float)size;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    if (size == 0){
        throw std::runtime_error("Size Not Valid");
    }
    float cov = 0;
    for (int i = 0; i < size; i++){
        cov += x[i]*y[i];
    }
    cov = cov / size;

    return cov - avg(x,size)*avg(y,size);
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
    if (size == 0){
        throw std::runtime_error("Size Not Valid");
    }
    float corr = cov(x, y, size) / ((sqrt(var(x, size))) * (sqrt(var(y, size))));
    return corr;
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){
    if (size == 0){
        throw std::runtime_error("Size Not Valid");
    }
    //int arrSize = sizeof(points) / sizeof(points[0]);
    float sumX = 0, sumY = 0, sumPowX = 0, sumXY = 0, a, b;
    for (int i = 0; i < size; i++) {
        sumX += points[i]->x;
        sumY += points[i]->y;
        sumPowX += (points[i]->x) * (points[i]->x);
        sumXY += (points[i]->x) * (points[i]->y);
    }
    a = (size*sumXY - sumX*sumY) / (size*sumPowX - sumX*sumX);
    b = (sumY - a*sumX) / size;

    return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    if (size == 0){
        throw std::runtime_error("Size Not Valid");
    }
    Line line;
    line = linear_reg(points, size);
    float linearVal = line.a * p.x + line.b;
    if (linearVal >= p.y){
        return linearVal - p.y;
    }
    return p.y - linearVal;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
    float linearVal = l.a * p.x + l.b;
    if (linearVal >= p.y){
        return linearVal - p.y;
    }
    return p.y - linearVal;
}
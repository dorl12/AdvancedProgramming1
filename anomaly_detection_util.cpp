
/*
 * animaly_detection_util.cpp
 *
 * Author: write your ID and name here
 */

#include <math.h>
#include "anomaly_detection_util.h"

float avg(float* x, int size){
    float sum = 0;
    for(int i = 1; i <= size;i++){
        sum += *x;
    }
    sum = sum / (float)size;
	return sum;
}

// returns the variance of X and Y
float var(float* x, int size){
    float sqDiff = 0;
    float mean = avg(x, size);
    for (int i = 0; i < size; i++) {
        sqDiff += (*x - mean) * (*x - mean);
    }
    return sqDiff / n;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    float Ex = avg(x, size);
    float Ey = avg(y, size);
    float xy = (*x) * (*y);
    float* xy_f = &xy;
    float Exy = avg(xy_f, size);
    float cov = Exy - (Ex*Ey);
	return cov;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
	float corr = cov(x, y, size) / sqrt(avg(x, size)) * sqrt(avg(y, size));
    return corr;
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){
    int arrSize = sizeof(points) / sizeof(points[0]);
    float sumX = 0, sumY = 0, sumPowX = 0, sumXY = 0, a, b;
    for (int i = 0; i < arrSize; i++) {
        sumX += *points[i]->x;
        sumY += *points[i]->y;
        sumPowX += (*points[i]->x) * (*points[i]->x);
        sumXY += (*points[i]->x) * (*points[i]->y);
    }

    a = (arrSize*sumXY - sumX*sumY) / (arrSize*sumPowX - sumX*sumX);
    b = (sumY - a*sumX) / arrSize;

	return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
	return 0;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	return 0;
}

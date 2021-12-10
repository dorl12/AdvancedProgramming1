
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);

// you can add here additional methods
double eucDist(const Point& firstPoint, const Point& secondPoint);
bool isInsideTheCircle(const Circle& circle, const Point& point);
Point calculateCenter(double x1, double y1, double x2, double y2);
Circle circleFromThreePoints(const Point& firstPoint, const Point& secondPoint, const Point& thirdPoint);
Circle circleFromTwoPoints(const Point& firstPoint, const Point& secondPoint);
bool isValidCircle(const Circle& circle, const vector<Point>& vectorOfPoints);
Circle trivialMinCircle(vector<Point> vectorOfPoints);
Circle minCircleWelzlAlgo(Point** inputPoints, vector<Point> pointsOnBoundary, int numOfPoints);


#endif /* MINCIRCLE_H_ */

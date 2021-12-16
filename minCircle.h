/*
 * minCircle.h
 *
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */
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

float Dist(const Point& firstPoint, const Point& secondPoint);
// returns the minimum circle enclosing the given points
Circle findMinCircle(Point** points,size_t size);
// returns the euclidean distance between two points
float eucDist(const Point& firstPoint, const Point& secondPoint);
// checks whether the given point lies inside the circle or on the boundaries
bool isInsideTheCircle(const Circle& circle, const Point& point);
// returns a point which is the center of a circle defined by three points
Point calculateCenter(float x1, float y1, float x2, float y2);
// returns the smallest circle defined by three points
Circle circleFromThreePoints(const Point& firstPoint, const Point& secondPoint, const Point& thirdPoint);
// returns the smallest circle defined by two points
Circle circleFromTwoPoints(const Point& firstPoint, const Point& secondPoint);
// checks whether a circle encloses the given points
bool isValidCircle(const Circle& circle, const vector<Point>& vectorOfPoints);
// returns the minimum circle of up to three points
Circle trivialMinCircle(vector<Point> vectorOfPoints);
/*
    returns the minimum circle using Welzl's algorithm
    the function gets an array of pointers to points,
    a vector of points on the boundary of the circle
    and a number of points in the array which are not
    yet processed and returns the minimum circle that
    contains all the points
 */
Circle minCircleWelzlAlgo(Point** inputPoints, vector<Point> pointsOnBoundary, int numOfPoints);


#endif /* MINCIRCLE_H_ */

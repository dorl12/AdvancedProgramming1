/*
 * minCircle.cpp
 *
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */
#include <math.h>
#include "minCircle.h"

// returns the euclidean distance between two points
float eucDist(const Point& firstPoint, const Point& secondPoint) {
    return sqrt(pow(firstPoint.x - secondPoint.x, 2) + pow(firstPoint.y - secondPoint.y, 2));
}

// checks whether the given point lies inside the circle or on the boundaries
bool isInsideTheCircle(const Circle& circle, const Point& point) {
    return eucDist(circle.center, point) <= circle.radius;
}

// returns a point which is the center of a circle defined by three points
Point calculateCenter(float x1, float y1, float x2, float y2) {
    float a = x1 * x1 + y1 * y1;
    float b = x2 * x2 + y2 * y2;
    float c = x1 * y2 - y1 * x2;
    return Point((y2 * a - y1 * b) / (2 * c), (x1 * b - x2 * a) / (2 * c));
}

// returns the smallest circle defined by three points
Circle circleFromThreePoints(const Point& firstPoint, const Point& secondPoint, const Point& thirdPoint) {
    // calculating the center point of the circle using the function calculateCenter
    Point center = calculateCenter(secondPoint.x - firstPoint.x, secondPoint.y - firstPoint.y,
                                   thirdPoint.x - firstPoint.x, thirdPoint.y - firstPoint.y);
    center.x += firstPoint.x;
    center.y += firstPoint.y;
    return Circle(center, eucDist(center, firstPoint));
}

// returns the smallest circle defined by two points
Circle circleFromTwoPoints(const Point& firstPoint, const Point& secondPoint) {
    // the center of the circle is the middle between the first point and the second point
    Point center = Point((firstPoint.x + secondPoint.x) / 2.0, (firstPoint.y + secondPoint.y) / 2.0);
    // the radius of the circle is the half distance of the first point and the second point
    return Circle(center, eucDist(firstPoint, secondPoint) / 2.0);
}

// checks whether a circle encloses the given points
bool isValidCircle(const Circle& circle, const vector<Point>& vectorOfPoints) {
    for (const Point& p : vectorOfPoints) {
        // in case the given point is not inside the circle, the circle is not valid
        if (!isInsideTheCircle(circle, p)) {
            return false;
        }
    }
    // in case all the points in the vector are inside the circle, the circle is valid
    return true;
}

// returns the minimum circle of up to three points
Circle trivialMinCircle(vector<Point> vectorOfPoints) {
    // in case there are more than three points, throw runtime exception
    if (vectorOfPoints.size() > 3) {
        throw std::runtime_error("Too many points");
    }
    // in case there are no points, return a circle in which the center is (0,0) and the radius is 0
    if (vectorOfPoints.empty()) {
        return Circle(Point(0 , 0), 0);
    }
    /*
        in case there is one point, return a circle in which the center is the first point
        in the vector and the radius is 0
     */
    else if (vectorOfPoints.size() == 1) {
        return Circle(vectorOfPoints[0], 0);
    }
    /*
        in case there are two points, return a circle by calling to the function circleFromTwoPoints
        with the first and the second points in the vector
     */
    else if (vectorOfPoints.size() == 2) {
        return Circle(circleFromTwoPoints(vectorOfPoints[0], vectorOfPoints[1]));
    }
    // in case there are three points, check whether the circle can be defined using two points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            // define a circle using two points
            Circle circle = circleFromTwoPoints(vectorOfPoints[i], vectorOfPoints[j]);
            // return the circle in case it is valid
            if (isValidCircle(circle, vectorOfPoints)) {
                return circle;
            }
        }
    }
    // return a circle defined by the first three points in the vector
    return circleFromThreePoints(vectorOfPoints[0], vectorOfPoints[1], vectorOfPoints[2]);
}

/*
    returns the minimum circle using Welzl's algorithm
    the function gets an array of pointers to points,
    a vector of points on the boundary of the circle
    and a number of points in the array which are not
    yet processed and returns the minimum circle that
    contains all the points
 */
Circle minCircleWelzlAlgo(Point** inputPoints, vector<Point> pointsOnBoundary, int numOfPoints) {
    // in case all the points are processed or the num of pointsOnBoundary is three, call trivialMinCircle
    if (numOfPoints == 0 || pointsOnBoundary.size() == 3) {
        return trivialMinCircle(pointsOnBoundary);
    }
    // calculate a random index using the function rand()
    int randomIndex = rand() % numOfPoints;
    // getting a random point from the array according to the index
    Point point = *inputPoints[randomIndex];
    // put the point at the end of the array
    swap(inputPoints[randomIndex], inputPoints[numOfPoints - 1]);
    // calling the function recursively without the random point
    Circle circle = minCircleWelzlAlgo(inputPoints, pointsOnBoundary, numOfPoints - 1);
    // in case the calculated circle contains the random point, return the circle
    if (isInsideTheCircle(circle, point)) {
        return circle;
    }
    // else, add the random point to the vector of points on the boundary of the circle
    pointsOnBoundary.push_back(point);
    /*
        calling the function recursively with the inputPoints without
        the random point and with the random point included in the pointsOnBoundary
     */
    return minCircleWelzlAlgo(inputPoints, pointsOnBoundary , numOfPoints - 1);
}

// returns the minimum circle enclosing the given points
Circle findMinCircle(Point** points,size_t size) {
    return minCircleWelzlAlgo(points, {}, size);
}



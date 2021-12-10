/*
 * minCircle.cpp
 *
 * Author: 316460146 Hadar Pinto
 *         313547085 Dor Levy
 */
#include <math.h>
#include "minCircle.h"

double eucDist(const Point& firstPoint, const Point& secondPoint) {
    return sqrt(pow(firstPoint.x - secondPoint.x, 2) + pow(firstPoint.y - secondPoint.y, 2));
}

bool isInsideTheCircle(const Circle& circle, const Point& point) {
    return eucDist(circle.center, point) <= circle.radius;
}

Point calculateCenter(double x1, double y1, double x2, double y2) {
    double a = x1 * x1 + y1 * y1;
    double b = x2 * x2 + y2 * y2;
    double c = x1 * y2 - y1 * x2;
    return Point((y2 * a - y1 * b) / (2 * c), (x1 * b - x2 * a) / (2 * c));
}

Circle circleFromThreePoints(const Point& firstPoint, const Point& secondPoint, const Point& thirdPoint) {
    Point center = calculateCenter(secondPoint.x - firstPoint.x, secondPoint.y - firstPoint.y,
                                   thirdPoint.x - firstPoint.x, thirdPoint.y - firstPoint.y);
    center.x += firstPoint.x;
    center.y += firstPoint.y;
    return Circle(center, eucDist(center, firstPoint));
}

Circle circleFromTwoPoints(const Point& firstPoint, const Point& secondPoint) {
    Point center = Point((firstPoint.x + secondPoint.x) / 2.0, (firstPoint.y + secondPoint.y) / 2.0);
    return Circle(center, eucDist(firstPoint, secondPoint) / 2.0);
}

bool isValidCircle(const Circle& circle, const vector<Point>& vectorOfPoints) {
    for (const Point& p : vectorOfPoints) {
        if (!isInsideTheCircle(circle, p)) {
            return false;
        }
    }
    return true;
}

Circle trivialMinCircle(vector<Point> vectorOfPoints) {
    if (vectorOfPoints.size() > 3) {
        throw std::runtime_error("Size Not Valid");
    }
    if (vectorOfPoints.empty()) {
        return Circle(Point(0 , 0), 0);
    }
    else if (vectorOfPoints.size() == 1) {
        return Circle(vectorOfPoints[0], 0);
    }
    else if (vectorOfPoints.size() == 2) {
        return Circle(circleFromTwoPoints(vectorOfPoints[0], vectorOfPoints[1]));
    }
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            Circle circle = circleFromTwoPoints(vectorOfPoints[i], vectorOfPoints[j]);
            if (isValidCircle(circle, vectorOfPoints)) {
                return circle;
            }
        }
    }
    return circleFromThreePoints(vectorOfPoints[0], vectorOfPoints[1], vectorOfPoints[2]);
}

Circle minCircleWelzlAlgo(Point** inputPoints, vector<Point> pointsOnBoundary, int numOfPoints) {
    if (numOfPoints == 0 || pointsOnBoundary.size() == 3) {
        return trivialMinCircle(pointsOnBoundary);
    }
    int randomIndex = rand() % numOfPoints;
    Point point = *inputPoints[randomIndex];
    swap(inputPoints[randomIndex], inputPoints[numOfPoints - 1]);
    Circle circle = minCircleWelzlAlgo(inputPoints, pointsOnBoundary, numOfPoints - 1);
    if (isInsideTheCircle(circle, point)) {
        return circle;
    }
    pointsOnBoundary.push_back(point);
    return minCircleWelzlAlgo(inputPoints, pointsOnBoundary , numOfPoints - 1);
}

Circle findMinCircle(Point** points,size_t size) {
    
}


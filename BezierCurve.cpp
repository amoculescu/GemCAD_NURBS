#include "BezierCurve.h"

#include <stdio.h>		// cout
#include <iostream>		// cout


BezierCurve::BezierCurve(bool isRational_)
        : rational(isRational_) {
}

BezierCurve::BezierCurve(const std::vector<Vec3f> &controlPoints_, bool isRational_)
        : controlPoints(controlPoints_), rational(isRational_) {
}

void BezierCurve::push(Vec3f ctrlPt) {
    controlPoints.push_back(ctrlPt);
}

// splits the bezier curve into two at u=t
std::pair<BezierCurve, BezierCurve> BezierCurve::separateCurveAt(const float t) {
    int n = controlPoints.size() - 1; //grade of curve
    std::vector<Vec3f> cps1, cps2, tempVector;
    if(rational == true)
    {
        //put every control point of curve into tempVector
        for (int i = 0; i <= n; i++)
        {
            tempVector.push_back(controlPoints[i] / controlPoints[i].z);
        }
        /*
         *first point of original curve == first point of first curve,
         * last point of original curve == last point of second curve
         */
        cps1.push_back(tempVector[0]);
        cps2.push_back(tempVector[tempVector.size() - 1]);

        //split every segment at t, create new points and push to respective curve
        for (int i = 0; i < n; i++)
        {
            //only add second "parent" if new point isn't last or second to last
            if (tempVector.size() > 2)
            {
                //cps1.push_back(tempVector[1]);
                //cps2.push_back(tempVector[tempVector.size() - 2]);
            }
            //split curve at t
            for (int k = 0; k < n - i; k++)
            {
                tempVector[k] = (1 - t) * tempVector[k] + tempVector[k + 1] * t;
            }
            //first point calculated == next point of first curve
            cps1.push_back(tempVector[0]);
            //remove last point (not needed anymore)
            tempVector.pop_back();
            //last point calculated == last point of second curve
            cps2.push_back(tempVector[tempVector.size() - 1]);
        }
    }
    else
    {
        //put every control point of curve into tempVector
        for (int i = 0; i <= n; i++)
        {
            tempVector.push_back(controlPoints[i]);
        }
        /*
         *first point of original curve == first point of first curve,
         * last point of original curve == last point of second curve
         */
        cps1.push_back(tempVector[0]);
        cps2.push_back(tempVector[tempVector.size() - 1]);

        //split every segment at t, create new points and push to respective curve
        for (int i = 0; i < n; i++)
        {
            //only add second "parent" if new point isn't last or second to last
            if (tempVector.size() > 2)
            {
                cps1.push_back(tempVector[1]);
                cps2.push_back(tempVector[tempVector.size() - 2]);
            }
            //split curve at t
            for (int k = 0; k < n - i; k++)
            {
                tempVector[k] = (1 - t) * tempVector[k] + tempVector[k + 1] * t;
            }
            //first point calculated == next point of first curve
            cps1.push_back(tempVector[0]);
            //remove last point (not needed anymore)
            tempVector.pop_back();
            //last point calculated == last point of second curve
            cps2.push_back(tempVector[tempVector.size() - 1]);
        }
    }
    //reverse control point order of curve 2
    std::reverse(cps2.begin(), cps2.end());
    //create curves
    BezierCurve curve1(cps1, rational);
    BezierCurve curve2(cps2, rational);
    //return curves as pair
    return std::pair<BezierCurve, BezierCurve>(curve1, curve2);
}

// evaluates the bezier curve at u=t, returns that point and calculates its tangent
Vec3f BezierCurve::evaluateCurveAt(const float t, Vec3f &tangent) {
    Vec3f point;
    //separate curve at t
    std::pair<BezierCurve, BezierCurve> curves = separateCurveAt(t);
    //point asked for is first point of second curve or last point of first curve; i went with the former
    point = curves.second.getControlPoints()[0];
    //vector from point to second control point of second curve as the directional vector of tangent
    tangent = curves.second.getControlPoints()[1] - point;
    return point;
}

std::pair<std::vector<Vec3f>, std::vector<Vec3f>> BezierCurve::evaluateCurve(const size_t numberSamples) {
    std::vector<Vec3f> points;
    points.reserve(numberSamples);
    std::vector<Vec3f> tangents;
    tangents.reserve(numberSamples);
    //calculate interval
    float t = 1.0f / numberSamples;

    //gets points every t
    for (float i = 0.0; i <= 1.0; i += t) {
        //create empty tangent
        Vec3f *aTangent = new Vec3f();
        tangents.push_back(*aTangent);
        Vec3f point = evaluateCurveAt(i, tangents[i]);
        points.push_back(point);
    }
    //return pair of points and tangents
    return std::make_pair(points, tangents);
}

std::ostream &operator<<(std::ostream &os, BezierCurve &bezierCurve) {
    if (bezierCurve.controlPoints.empty()) {
        os << "Bezier curve without control points!";
        return os;
    }
    // degree
    os << "Bezier curve, degree " << bezierCurve.controlPoints.size() - 1 << "\n";
    // control points
    for (size_t i = 0; i < bezierCurve.controlPoints.size(); i++)
        os << "  " << bezierCurve.controlPoints[i] << std::endl;
    return os;
}

#include "BezierCurve.h"

#include <stdio.h>		// cout
#include <iostream>		// cout


BezierCurve::BezierCurve(bool isRational_)
    : rational(isRational_)
{
}

BezierCurve::BezierCurve(const std::vector<Vec3f>& controlPoints_, bool isRational_)
    : controlPoints(controlPoints_)
    , rational(isRational_)
{
}

void BezierCurve::push(Vec3f ctrlPt)
{
    controlPoints.push_back(ctrlPt);
}

// splits the bezier curve into two at u=t
std::pair<BezierCurve, BezierCurve> BezierCurve::separateCurveAt(const float t)
{
    int n = controlPoints.size() - 1;
    if(n != 1)
    {
        std::vector<Vec3f> cps1, cps2;
        float n = controlPoints.size() - 1;
        std::vector<Vec3f> ptArray;
        std::vector<Vec3f> tempArray;
        
        for(int i = 0; i <= n; i++)
        {
            Vec3f point = controlPoints[i];
            ptArray.push_back(point);
        }
        cps1.push_back(ptArray[0]);
        cps2.push_back(ptArray.back());
        for(int i = 0; i < n; i++)
        {
            for(int k = 0; k < n - i; k++)
            {
                Vec3f myPoint = ptArray[k + 1] *  t + ptArray[k] *  t;
                tempArray.push_back(myPoint);
            }
            cps1.push_back(tempArray[0]);
            cps2.insert(cps2.begin(), tempArray.back());
            ptArray = tempArray;
            tempArray.clear();
        }
        
        BezierCurve curve1(cps1, rational);
        BezierCurve curve2(cps2, rational);
        return std::pair<BezierCurve, BezierCurve>(curve1, curve2);
    }

    // TODO: implement the de Casteljau algorithm and create two separated bezier curves with the new control points.
    // ==========================================================================================================

    // ==========================================================================================================
}
// evaluates the bezier curve at u=t, returns that point and calculates its tangent
Vec3f BezierCurve::evaluateCurveAt(const float t, Vec3f &tangent)
{
    Vec3f point;
    BezierCurve differential = calcDifferential();
    std::pair<BezierCurve, BezierCurve> differentialCurves = differential.separateCurveAt(t);
    tangent = differentialCurves.second.getControlPoints().front();
    
    std::pair<BezierCurve, BezierCurve> curves = separateCurveAt(t);
    point = curves.second.getControlPoints().front();
    
    
    // TODO: implement the evaluation of the bezier curve and the tangent at t.
    // Note: use the seperateCurveAt(t) function.
    // ==========================================================================================================


    // ==========================================================================================================
    return point;
}

BezierCurve BezierCurve::calcDifferential()
{
    std::vector<Vec3f> ptArray;
    for(int i = 0; i < controlPoints.size(); i++)
    {
        if(i == 0)
        {
            ptArray.push_back(controlPoints[1]);
        }
        else if (i == controlPoints.size() - 1)
        {
            ptArray.push_back(controlPoints[i]);
        }
        else
        {
            Vec3f point = controlPoints[i + 1] - controlPoints[i];
            ptArray.push_back(point);
        }
    }
    BezierCurve result(ptArray, rational);
    return result;
}

std::pair<std::vector<Vec3f>, std::vector<Vec3f>> BezierCurve::evaluateCurve(const size_t numberSamples)
{
    std::vector<Vec3f> points;
    points.reserve(numberSamples);
    std::vector<Vec3f> tangents;
    tangents.reserve(numberSamples);
    // TODO: implement evaluation of the bezier curve at 'numberSamples' equidistant points
    // Note: use the 'evaluateCurveAt' function.
    // ==========================================================================================================


    // ==========================================================================================================

    return std::make_pair(points,tangents);
}

std::ostream& operator<< (std::ostream& os, BezierCurve& bezierCurve)
{
    if(bezierCurve.controlPoints.empty())
    {
        os << "Bezier curve without control points!";
        return os;
    }
    // degree
    os << "Bezier curve, degree " << bezierCurve.controlPoints.size() - 1 << "\n";
    // control points
    for(size_t i = 0; i < bezierCurve.controlPoints.size(); i++) os << "  " << bezierCurve.controlPoints[i] << std::endl;
    return os;
}

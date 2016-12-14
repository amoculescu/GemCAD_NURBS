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
        float n = getControlPoints().size() - 1;
        auto ptrToFirst = controlPoints.begin();
        auto ptrToLast = controlPoints.end();
        Vec3f* ptArray[int(n + 1)][int(n + 1)];
        int counter;

        while(*ptrToFirst != *ptrToLast)
        {
            *(ptArray[0][counter]) = *ptrToFirst;
            std::advance(ptrToFirst, 1);
            counter++;
        }
        counter = n;
        for(int i = 0; i <= n; i++)
        {
            for(int j = 0; j <= counter; j++)
            {

                *(ptArray[i + 1][j]) = (*(ptArray[i][j]) + *(ptArray[i][j + 1])) * t;
            }
            counter--;
        }
        for(int i = 0; i <= n; i++)
        {
            for(int j = 0; j <= n - 1; j++)
            {
                std::cout << "ptArray[" << i << "][" << j << "]: " << *(ptArray[i][j]) << std::endl;
            }
        }

        counter = n;
        for(int i = 0; i <= n; i++)
        {
            cps1.push_back(*(ptArray[i][0]));
            cps2.push_back(*(ptArray[int(counter)][i]));
            counter--;
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
    // TODO: implement the evaluation of the bezier curve and the tangent at t.
    // Note: use the seperateCurveAt(t) function.
    // ==========================================================================================================


    // ==========================================================================================================
    return point;
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

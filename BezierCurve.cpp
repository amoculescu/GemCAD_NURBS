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
	std::vector<Vec3f> cps1, cps2;
	
	// TODO: implement the de Casteljau algorithm and create two separated bezier curves with the new control points.
	// ==========================================================================================================
	
	
	// ==========================================================================================================
	BezierCurve curve1(cps1, rational);
	BezierCurve curve2(cps2, rational);
	return std::pair<BezierCurve, BezierCurve>(curve1, curve2);
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

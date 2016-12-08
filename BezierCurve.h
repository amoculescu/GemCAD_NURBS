#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include <stdlib.h>		// standard library
#include <vector>		// std::vector<>

#include "Vec3.h"		// vector (x, y, z)

// for this bezier curve class we assume the curve is ALWAYS parameterized within [0, 1]!
class BezierCurve
{

public:

	// empty constructor which generates a curve with NO control points
	BezierCurve(bool isRational = false);

	// constructor which takes given control points
	BezierCurve(const std::vector<Vec3f>& controlPoints_, bool isRational = false);

	// evaluate the curve at parameter t with de Casteljau algorithm. Returns both bezier curves seperated at parameter t.
	std::pair<BezierCurve, BezierCurve> separateCurveAt(const float t);

	// evaluate the curve at parameter t with de Casteljau algorithm. Returns the evaluated point and its tangent at parameter t.
	Vec3f evaluateCurveAt(const float t, Vec3f &tangent);
	
	// evaluate the curve with de Casteljau algorithm at numberSamples sample points. Returns the evaluated points and their tangents.
	std::pair<std::vector<Vec3f>, std::vector<Vec3f>> evaluateCurve(const size_t numberSamples);

	// getting references to the data
	const std::vector<Vec3f>& getControlPoints() const { return controlPoints; }

	// getting rational flag
	bool isRational() const { return rational; }

	// overloading the << operator to print our information of the class. declared as friend, so the function has access to private members.
	friend std::ostream& operator<< (std::ostream& os, BezierCurve& bezierCurve);

private:

	// class data:
	std::vector<Vec3f> controlPoints;
	bool rational;

};

// ostream << operator. E.g. use "std::cout << bezierCurve << std::endl;"
std::ostream& operator<< (std::ostream& os, BezierCurve& bezierCurve);

#endif
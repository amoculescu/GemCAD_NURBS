#ifndef NURBS_CURVE_H
#define NURBS_CURVE_H

#include <stdlib.h>		// standard library
#include <vector>		// std::vector<>

#include "Vec4.h"		// vector (x, y, z, w)

class NURBSCurve {

public:

	// empty constructor which creates a degree 2 quarter circle in first quadrant, XY-plane
	NURBSCurve();

	// constructor which takes given control points P, knot vector U and degree p
	NURBSCurve(const std::vector<Vec4f>& controlPoints_, const std::vector<float>& knotVector_, const unsigned int degree_);

    void changeWeight(int pos, float newWeight);

	// insert a knot with deBoor algorithm. returns false, if newKnot is not within begin and end parameter.
	bool insertKnot(const float newKnot);

	// evaluate the curve at parameter t with deBoor (inserting a knot until its multiplicity is p). also returns the tangent at the evaluated point.
	Vec4f evaluteDeBoor(const float t, Vec4f& tangent);

	// returns false if the knot vector is not sorted or if the dimensions of knot vector, control points and degree do not match
	bool isValidNURBS();

	// getting references to the control points
	const std::vector<Vec4f>& getControlPoints() const { return controlPoints; }

	// getting reference to knot vector
	std::vector<float>& getKnotVector() { return knotVector; }

	// getting degree
	unsigned int getDegree() { return degree; }
	
	// evaluate the curve with deBoor algorithm at numberSamples sample points. Returns the evaluated points and their tangents.
	std::pair<std::vector<Vec4f>, std::vector<Vec4f>> evaluateCurve(const size_t numberSamples);

private:

	// class data:
	std::vector<Vec4f> controlPoints;
	std::vector<float> knotVector;
	unsigned int degree;



};

// ostream << operator. E.g. use "std::cout << nurbs << std::endl;"
std::ostream& operator<< (std::ostream& os, NURBSCurve& nurbsCurve);

#endif // NURBS_CURVE_H
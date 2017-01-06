#include "NURBSCurve.h"

#include <stdio.h>		// cout
#include <iostream>		// cout

NURBSCurve::NURBSCurve()
{
	
	isValidNURBS();
}

/*
 * p == grad der kurve; mindestens 2
 * P == Kontrollpunkte; mindestens so viele wie der grad der kurve
 * U == Knotenvektor; anzahl == p + P
 */

// constructor which takes given control points P, knot vector U and degree p
NURBSCurve::NURBSCurve(const std::vector<Vec4f>& controlPoints_, const std::vector<float>& knotVector_, const unsigned int degree_)
	: controlPoints(controlPoints_)
	, knotVector(knotVector_)
	, degree(degree_)
{
	isValidNURBS();
}

bool NURBSCurve::isValidNURBS()
{
	// knot vector verification
	bool validU = true;
	for (unsigned int i = 1; i < knotVector.size() && validU == true; i++)
    {
        if (knotVector[i] < knotVector[i-1])
	    {
		   std::cout << "INVALID (unsorted) knotVector.\n";
		   validU = false;
		   break;
		}
	}
	// size verification
	bool validSize = true;
	if (controlPoints.size() + degree + 1 != knotVector.size()) 
	{
		std::cout << "INVALID sizes (controlPoints.size() + degree + 1 != knotVector.size()).\n";
		validSize = false;
	}
	return (validU && validSize);
}


bool NURBSCurve::insertKnot(const float newKnot)
{
	// TODO: implement knot insertion with de boor algorithm
	// =====================================================

    if (newKnot <= knotVector[0] || newKnot >= knotVector[knotVector.size() - 1])
    {
        return false;
    }
    else
    {
        for (unsigned int i = 1; i < knotVector.size(); i++)
        {
            if (newKnot <= knotVector[i] && newKnot >= knotVector[i + 1])
            {
                for (int h = i + 1; h < controlPoints.size(); h++)
                {
                    controlPoints[h + 1] = controlPoints[h];
                }
                for (int j = i - degree + 1; j <= i; j++)
                {
                    float alpha = (newKnot - knotVector[j]) / (knotVector[j + degree] - knotVector[j]);
                    controlPoints[j] = alpha*controlPoints[j] + (1 - alpha)*controlPoints[j - 1];
                }
                knotVector.insert(knotVector.begin() + i + 1, newKnot);
                return true;
            }
        }
    }

	// =====================================================
	return true;
}

Vec4f NURBSCurve::evaluteDeBoor(const float t, Vec4f& tangent)
{
	// create a copy of this NURBS curve
	NURBSCurve tempNURBS(*this);
	Vec4f point;
	// TODO: use insertKnot to evaluate the curve and its tangent. Take care to NOT modify this NURBS curve. Instead use the temporary copy.
	// =====================================================================================================================================

 	// =====================================================================================================================================
	return point;
}


std::pair<std::vector<Vec4f>, std::vector<Vec4f>> NURBSCurve::evaluateCurve(const size_t numberSamples)
{
	std::vector<Vec4f> points;
	points.reserve(numberSamples);
	std::vector<Vec4f> tangents;
	tangents.reserve(numberSamples);
	// TODO: implement evaluation of the NURBS curve at 'numberSamples' equidistant points
	// Note: use the evaluteDeBoor(t) function. 
	// ==========================================================================================================


	// ==========================================================================================================

	return std::make_pair(points,tangents);
}

std::ostream& operator<< (std::ostream& os, NURBSCurve& nurbs)
{
	// degree
	os << "NURBS curve, degree " << nurbs.getDegree() << "\n";
	// control points
	os << "  " << nurbs.getControlPoints().size() << " controlPoints:\n";
	for (unsigned int i = 0; i < nurbs.getControlPoints().size(); i++) os << "    " << nurbs.getControlPoints()[i] << "\n";
	// knot vector
	os << "  " << nurbs.getKnotVector().size() << " knotVector: ";
	for (unsigned int i = 0; i < nurbs.getKnotVector().size(); i++) os << nurbs.getKnotVector()[i] << ", ";
	os << "\n";
	// knot vector verification
	nurbs.isValidNURBS();
	return os;
}
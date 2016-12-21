#define RADPERDEG 0.0174533

#include "stdio.h"
#include "iostream"
#include "CurveRendering.h"
#include <cmath>
#include <GLUT/glut.h>
#include <BezierCurve.h>
#include <NURBSCurve.h>
#include <algorithm>


void drawBezier(BezierCurve &bezierCurve, Vec3f color)
{
    auto ptrToCtrlPoint = bezierCurve.getControlPoints().begin();
    float bernstein;
    float n = bezierCurve.getControlPoints().size() - 1;

    glBegin(GL_LINE_STRIP);
    glColor3fv(&color.x);
    for (float u = 0; u <= 1; u += 0.005)
    {
        Vec3f p;
        ptrToCtrlPoint = bezierCurve.getControlPoints().begin();
        for(int i = 0; i <= n; i++)
        {
            bernstein = calcBernstein(n, i, u);
            Vec3f b = *ptrToCtrlPoint;
            Vec3f b2 = b * bernstein;
            p += b2;
            //std::cout << "bernstein: " << bernstein << " b: " << b << " b2: " << b2 << " p: " << p << std::endl;
            if(*ptrToCtrlPoint != bezierCurve.getControlPoints().back())
            {
                std::advance(ptrToCtrlPoint, 1);
            }
         }
        glVertex3fv(&p.x);
    }
    glEnd();
}

float calcBernstein(int n, int i, float u)
{
    float result;
    if(i == 0)
    {
        result = pow((1 - u), n);
    }
    else if( n == i)
    {
        result = pow(u, i);
    }
    else
    {
        result = binCoefficient(n, i) * pow((1 - u), (n - i)) * pow(u, i);
    }
    //std::cout << "b(u), n: " << n << " i: " << i << " = " << result << std::endl;
    //std::cout << "berstein polynomial: " << result << std::endl;
    return result;
}

float binCoefficient(int n, int i)
{
    float a = factorial(n);
    float b = factorial(i);
    float c = factorial(n - i);
    float result = a / (b * c);
    //std::cout << "binomial coefficient: " << result << std::endl;
    return result;
}

float factorial(float n)
{
    float result = 1;
    if(n != 0)
    {
         for(int i = 1; i <= n; i++)
        {
            result *= i;
        }
    }
    //std::cout << "factorial: " << result << std::endl;
    return result;
}

void drawBezierCtrlPolygon(const BezierCurve &bezierCurve, Vec3f color)
{
     glBegin(GL_POINTS);
     glColor3fv(&color.x);
     for(int i = 0; i < bezierCurve.getControlPoints().size(); i++)
     {
         glVertex3fv(&bezierCurve.getControlPoints()[i].x);
     }
     glEnd();

	// TODO: implement the visualization of the 3D bezier curves control polygon (e.g. with GL_LINE_STRIP)
	// ===============================================================================
	// cps of the complete curve


	// ===============================================================================
}

void drawRationalBezier(BezierCurve &bezierCurve, Vec3f color)
{
	if (bezierCurve.isRational())
	{
        // TODO: implement the visualization of the 2D rational bezier curve in the plane w=1 (e.g. with GL_LINE_STRIP)
        // ===============================================================================


        // ===============================================================================
    }
}
void drawRationalBezierCtrlPolygon(const BezierCurve &bezierCurve, Vec3f color)
{
	if (bezierCurve.isRational())
	{
        glBegin(GL_POINTS);
        glColor3fv(&color.x);
        for(int i = 0; i < bezierCurve.getControlPoints().size(); i++)
        {
           glVertex3fv(&bezierCurve.getControlPoints()[i].x);
        }
        glEnd();
    }
}

void drawNURBS(NURBSCurve &nurbsCurve, Vec3f color)
{
	// TODO: draw NURBS curve
	// NOT homogenized
	// ===================================================================================


	// ===================================================================================
}
void drawNURBS_H(NURBSCurve &nurbsCurve, Vec3f color)
{
	// TODO: draw NURBS curve
	// homogenized
	// ===================================================================================


	// ===================================================================================
}
void drawNURBSCtrlPolygon(const NURBSCurve &nurbsCurve, Vec3f color)
{
	// TODO: implement the visualization of the 
	// NOT homogenized 
	// NURBS' control polygon (e.g. with GL_LINE_STRIP)
	// =========================================================================================================


	// =========================================================================================================
}
void drawNURBSCtrlPolygon_H(const NURBSCurve &nurbsCurve, Vec3f color)
{
	// TODO: implement the visualization of the 
	// homogenized 
	// NURBS' control polygon (e.g. with GL_LINE_STRIP)
	// =========================================================================================================


	// =========================================================================================================
}

void renderBezier(BezierCurve &bezierCurve, Vec3f color)
{
	auto pointsAndTangents = bezierCurve.evaluateCurve(size_t(100));
	bool rational = bezierCurve.isRational();
	if (bezierCurve.isRational())
	{
		drawRationalBezier(bezierCurve, color);
	}
	if (rational)
		color = Vec3f(1.0f, 0.0f, 1.0f);
	drawBezier(bezierCurve, color);
}
void renderBezierEvaluation(BezierCurve &bezierCurve, float t)
{
	Vec3f color = { 1.0f,1.0f,1.0f };
	if (bezierCurve.getControlPoints().size() > 1)
	{
		bool rational = bezierCurve.isRational();
		auto twoBezierCurves = bezierCurve.separateCurveAt(t);

		glLineWidth(2.0f);

		// first partial curve cps
		if (rational)color = Vec3f(0.8f, 5.0f, 0.4f);
		else		color = Vec3f(0.8f, 0.0f, 0.4f);
		drawBezierCtrlPolygon(twoBezierCurves.first, color);
		// second partial curve cps		
		if (rational)color = Vec3f(0.4f, 5.0f, 0.8f);
		else		color = Vec3f(0.4f, 0.0f, 0.8f);
		drawBezierCtrlPolygon(twoBezierCurves.second, color);

		glLineWidth(1.0f);
		// cps of the complete curve
		if (rational)color = Vec3f(0.3f, 0.2f, 0.7f);
		else		color = Vec3f(0.3f, 0.7f, 0.7f);
		drawBezierCtrlPolygon(bezierCurve, color);

		glLineWidth(2.0f);
		if (bezierCurve.isRational())
		{

			auto twoBezierCurves2 = bezierCurve.separateCurveAt(t);
			// first partial curve cps
			color = Vec3f(0.8f, 0.0f, 0.4f);
			drawRationalBezierCtrlPolygon(twoBezierCurves2.first, color);
			// second partial curve cps
			color = Vec3f(0.4f, 0.0f, 0.8f);
			drawRationalBezierCtrlPolygon(twoBezierCurves2.second, color);
			glLineWidth(1.0f);
			// cps of the complete curve
			color = Vec3f(0.3f, 0.7f, 0.7f);
			drawRationalBezierCtrlPolygon(bezierCurve, color);

		}
	}

}

void renderNURBS(NURBSCurve &nurbsCurve)
{
	if (nurbsCurve.getControlPoints().size() > 1 && nurbsCurve.isValidNURBS())
	{
		// draw curve (x, y, w) not homogenized
		Vec3f color = Vec3f(1.0f, 0.8f, 0.0f);
		drawNURBS(nurbsCurve, color);
		color = Vec3f(0.8f, 1.0f, 0.0f);
		drawNURBS_H(nurbsCurve, color);
	}
}
void renderNURBSEvaluation(NURBSCurve &nurbsCurve, float t)
{
	Vec3f color = Vec3f(1.0f, 1.0f, 1.0f);
	if (!nurbsCurve.isValidNURBS())
		return;

	auto pointsAndTangents = nurbsCurve.evaluateCurve(size_t(50));
	auto points = pointsAndTangents.first;
	auto tangents = pointsAndTangents.second;

	if (points.size() > 1 && nurbsCurve.getControlPoints().size() > 1)
	{

		// draw control polygon (x, y, w) not homogenized
		color = Vec3f(0.7f, 0.5f, 0.0f);
		drawNURBSCtrlPolygon(nurbsCurve, color);
		// draw control polygon (x/w, y/w, w=1) homogenized
		color = Vec3f(0.7f, 0.0f, 0.7f);
		drawNURBSCtrlPolygon_H(nurbsCurve, color);

		// draw tangents of the not homogenized curve
		glColor3f(0.5f, 0.35f, 0.0f);
		glBegin(GL_LINES);
		for (unsigned int i = 0; i < tangents.size(); ++i)
		{
			auto p = points[i];
			auto t = tangents[i];
			t = Vec4f(t.w * p.x + p.w * t.x, t.w * p.y + p.w * t.y, t.w * p.z + p.w * t.z, 1.0f);
			glVertex3fv(&p.x);
			t = (t - p).normalized() + p;
			glVertex3fv(&t.x);
		}
		glEnd();
		// draw tangents of the homogenized curve
		glColor3f(0.5f, 0.0f, 0.5f);
		glBegin(GL_LINES);
		for (unsigned int i = 0; i < tangents.size(); ++i)
		{
			auto p = points[i];
			auto t = tangents[i];
			p = p / p.w;
			t = t / t.w;
			t = p + t;
			glVertex3fv(&p.x);
			t = (t - p).normalized() + p;
			glVertex3fv(&t.x);
		}
		glEnd();
	}
}

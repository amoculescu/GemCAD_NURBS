#define RADPERDEG 0.0174533

#include "stdio.h"
#include "iostream"
#include "CurveRendering.h"
#include <cmath>
#include <GL/glut.h>
#include "BezierCurve.h"
#include "NURBSCurve.h"
#include <algorithm>

#define numberOfPoints 1000

bool klickibunti = false;


void drawBezier(BezierCurve &bezierCurve, Vec3f color) {
    std::pair<std::vector<Vec3f>, std::vector<Vec3f>> points = bezierCurve.evaluateCurve(numberOfPoints);
    glBegin(GL_LINE_STRIP);
    if (klickibunti) {
        Vec3f color = setcolor();
        glColor3fv(&color.x);
    }
    else glColor3fv(&color.x);

    std::vector<Vec3f> myPointArray = points.first;
    for (float i = 0.0; i < myPointArray.size(); i++) {
        Vec3f myPoint = myPointArray[i];
        glVertex3fv(&myPoint.x);
    }
    glEnd();
}

void drawBezierCtrlPolygon(const BezierCurve &bezierCurve, Vec3f color) {
    glBegin(GL_LINE_STRIP); //make line
    if (klickibunti) {
        Vec3f color = setcolor();
        glColor3fv(&color.x);
    }
    else glColor3fv(&color.x); //color
    for (int i = 0; i < bezierCurve.getControlPoints().size(); i++) { //draw a line to every control point
        glVertex3fv(&bezierCurve.getControlPoints()[i].x);
    }
    glEnd();
}

void drawRationalBezier(BezierCurve &bezierCurve, Vec3f color) {
    if (bezierCurve.isRational()) {
        float n = bezierCurve.getControlPoints().size() - 1;
        std::vector<Vec3f> newCtrlPoints;

        for (int i = 0; i <= n; i++) {
            Vec3f point = bezierCurve.getControlPoints()[i] / bezierCurve.getControlPoints()[i].z;
            newCtrlPoints.push_back(point);
        }
        BezierCurve* newBezierCurve = new BezierCurve(newCtrlPoints, false);
        drawBezier(*newBezierCurve, color);
        //renderBezierEvaluation(*newBezierCurve, 0.5);
    }
}

void drawRationalBezierCtrlPolygon(const BezierCurve &bezierCurve, Vec3f color) {
    if (bezierCurve.isRational()) {
        glBegin(GL_LINE_STRIP);
        if (klickibunti) {
            Vec3f col = setcolor();
            glColor3fv(&col.x);
        }
        else glColor3fv(&color.x);
        for (int i = 0; i < bezierCurve.getControlPoints().size(); i++) {
            Vec3f point = bezierCurve.getControlPoints()[i] / bezierCurve.getControlPoints()[i].z;
            glVertex3fv(&point.x);
        }
        glEnd();
    }
}

void drawNURBS(NURBSCurve &nurbsCurve, Vec3f color)
{
    std::pair<std::vector<Vec4f>, std::vector<Vec4f>> points = nurbsCurve.evaluateCurve(numberOfPoints);
    std::vector<Vec4f> pointVector = points.first;
    glBegin(GL_LINE_STRIP);
    if (klickibunti) {
        Vec3f col = setcolor();
        glColor3fv(&col.x);
    }
    else {
        Vec3f testcol = Vec3f(0.0, 1.0, 0.0);
        glColor3fv(&testcol.x);
    }
    for (float i = 0.0; i < pointVector.size(); i++)
    {
        glVertex3f(pointVector[i].x, pointVector[i].y, pointVector[i].z);
    }
    glEnd();
}

void drawNURBS_H(NURBSCurve &nurbsCurve, Vec3f color) {
    std::pair<std::vector<Vec4f>, std::vector<Vec4f>> points = nurbsCurve.evaluateCurve(numberOfPoints);
    std::vector<Vec4f> pointVector = points.first;
    glBegin(GL_LINE_STRIP);
    if (klickibunti) {
        Vec3f col = setcolor();
        glColor3fv(&col.x);
    }
    else {
        Vec3f testcol = Vec3f(1.0, 1.0, 1.0);
        glColor3fv(&testcol.x);
    }
    for (float i = 0.0; i < pointVector.size(); i++)
    {
        Vec3f point = Vec3f{pointVector[i].x / pointVector[i].w,
                            pointVector[i].y / pointVector[i].w,
                            pointVector[i].z / pointVector[i].w};
        glVertex3fv(&point.x);
    }
    glEnd();
}

void drawNURBSCtrlPolygon(const NURBSCurve &nurbsCurve, Vec3f color) {
    glBegin(GL_LINE_STRIP); //make line
    if (klickibunti) {
        Vec3f col = setcolor();
        glColor3fv(&col.x);
    }
    else {
        Vec3f testcol = Vec3f(0.0, 0.0, 1.0);
        glColor3fv(&testcol.x); //color
    }
    for (int i = 0; i < nurbsCurve.getControlPoints().size(); i++) { //draw a line to every control point
        glVertex3f(nurbsCurve.getControlPoints()[i].x, nurbsCurve.getControlPoints()[i].y, nurbsCurve.getControlPoints()[i].z);
    }
    glEnd();
}

void drawNURBSCtrlPolygon_H(const NURBSCurve &nurbsCurve, Vec3f color) {
    glBegin(GL_LINE_STRIP); //make line
    if (klickibunti) {
        Vec3f col = setcolor();
        glColor3fv(&col.x);
    }
    else {
        Vec3f testcol = Vec3f(1.0, 0.0, 0.0);
        glColor3fv(&testcol.x); //color
    }
    for (int i = 0; i < nurbsCurve.getControlPoints().size(); i++) { //draw a line to every control point
        Vec3f point = {nurbsCurve.getControlPoints()[i].x / nurbsCurve.getControlPoints()[i].w,
                       nurbsCurve.getControlPoints()[i].y / nurbsCurve.getControlPoints()[i].w,
                       nurbsCurve.getControlPoints()[i].z / nurbsCurve.getControlPoints()[i].w};
        glVertex3fv(&point.x);
    }
    glEnd();
}

void renderBezier(BezierCurve &bezierCurve)
{
    auto pointsAndTangents = bezierCurve.evaluateCurve(size_t(100));
    bool rational = bezierCurve.isRational();
    Vec3f color;
    if (klickibunti) {
        color = setcolor();
    }
    else {
        color = Vec3f(0.0f, 1.0f, 1.0f);
    }
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
    Vec3f color;
    if (klickibunti) {
        color = setcolor();
    }
    else {
        color = { 1.0f,1.0f,1.0f };
    }
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

void renderNURBS(NURBSCurve &nurbsCurve) {
    if (nurbsCurve.getControlPoints().size() > 1 && nurbsCurve.isValidNURBS()) {
        // draw curve (x, y, w) not homogenized
        Vec3f color;
        if (klickibunti) {
            color = setcolor();
        }
        else {
            color = Vec3f(1.0f, 0.8f, 0.0f);
        }
        drawNURBS(nurbsCurve, color);
        color = Vec3f(0.8f, 1.0f, 0.0f);
        drawNURBS_H(nurbsCurve, color);
    }
}

void renderNURBSEvaluation(NURBSCurve &nurbsCurve, float t, bool flag)
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

		if (flag) {

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
}

Vec3f setcolor() {
    float a = rand() / (float)RAND_MAX;
    float b = rand() / (float)RAND_MAX;
    float c = rand() / (float)RAND_MAX;

    Vec3f vec =  Vec3f(a,b,c);
    return vec;
}

void setKlickiBunti()
{
    klickibunti = !klickibunti;
}

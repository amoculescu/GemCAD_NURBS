#define RADPERDEG 0.0174533

#include "stdio.h"
#include "iostream"
#include "CurveRendering.h"
#include <cmath>
#include <GL/glut.h>
#include "BezierCurve.h"
#include "NURBSCurve.h"
#include <algorithm>

#define numberOfPoints 2000


void drawBezier(BezierCurve &bezierCurve, Vec3f color) {
    std::pair<std::vector<Vec3f>, std::vector<Vec3f>> points = bezierCurve.evaluateCurve(numberOfPoints);
    glBegin(GL_LINE_STRIP);
    Vec3f col = setcolor();
    glColor3fv(&col.x);
    std::vector<Vec3f> myPointArray = points.first;
    for (float i = 0.0; i < myPointArray.size(); i++) {
        Vec3f myPoint = myPointArray[i];
        glVertex3fv(&myPoint.x);
    }
    glEnd();
}

void drawBezierCtrlPolygon(const BezierCurve &bezierCurve, Vec3f color) {
    glBegin(GL_LINE_STRIP); //make line
    Vec3f col = setcolor();
    glColor3fv(&col.x); //color
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
        drawBezier(*newBezierCurve, setcolor());
        //renderBezierEvaluation(*newBezierCurve, 0.5);
    }
}

void drawRationalBezierCtrlPolygon(const BezierCurve &bezierCurve, Vec3f color) {
    if (bezierCurve.isRational()) {
        glBegin(GL_LINE_STRIP);
        Vec3f col = setcolor();
        glColor3fv(&col.x);
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
    Vec3f testcol = setcolor();
    glColor3fv(&testcol.x);
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
    Vec3f testcol = setcolor();
    glColor3fv(&testcol.x);
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
    Vec3f testcol = setcolor();
    glColor3fv(&testcol.x); //color
    for (int i = 0; i < nurbsCurve.getControlPoints().size(); i++) { //draw a line to every control point
        glVertex3f(nurbsCurve.getControlPoints()[i].x, nurbsCurve.getControlPoints()[i].y, nurbsCurve.getControlPoints()[i].z);
    }
    glEnd();
}

void drawNURBSCtrlPolygon_H(const NURBSCurve &nurbsCurve, Vec3f color) {
    glBegin(GL_LINE_STRIP); //make line
    Vec3f testcol = setcolor();
    glColor3fv(&testcol.x); //color
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
    Vec3f color = setcolor();
    if (bezierCurve.isRational())
    {
        drawRationalBezier(bezierCurve, color);
    }
    if (rational)
        color = setcolor();
    drawBezier(bezierCurve, color);
}

void renderBezierEvaluation(BezierCurve &bezierCurve, float t)
{
    Vec3f color = setcolor();
    if (bezierCurve.getControlPoints().size() > 1)
    {
        bool rational = bezierCurve.isRational();
        auto twoBezierCurves = bezierCurve.separateCurveAt(t);

        glLineWidth(2.0f);

        // first partial curve cps
        if (rational)color = setcolor();
        else		color = setcolor();
        drawBezierCtrlPolygon(twoBezierCurves.first, color);
        // second partial curve cps
        if (rational)color = setcolor();
        else		color = setcolor();
        drawBezierCtrlPolygon(twoBezierCurves.second, color);

        glLineWidth(1.0f);
        // cps of the complete curve
        if (rational)color = setcolor();
        else		color = setcolor();
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
        Vec3f color = setcolor();
        drawNURBS(nurbsCurve, color);
        color = setcolor();
        drawNURBS_H(nurbsCurve, color);
    }
}

void renderNURBSEvaluation(NURBSCurve &nurbsCurve, float t) {
    Vec3f color = setcolor();
    if (!nurbsCurve.isValidNURBS())
        return;

    auto pointsAndTangents = nurbsCurve.evaluateCurve(numberOfPoints);
    auto points = pointsAndTangents.first;
    auto tangents = pointsAndTangents.second;

    if (points.size() > 1 && nurbsCurve.getControlPoints().size() > 1) {

        // draw control polygon (x, y, w) not homogenized
        drawNURBSCtrlPolygon(nurbsCurve, color);
        // draw control polygon (x/w, y/w, w=1) homogenized
        drawNURBSCtrlPolygon_H(nurbsCurve, color);
        // draw tangents of the not homogenized curve
        glColor3f(0.5f, 0.35f, 0.0f);
        /*glBegin(GL_LINES);
        for (unsigned int i = 0; i < tangents.size(); ++i)
        {
            Vec3f point1 = {points[i].x,
                            points[i].y,
                            points[i].z,};
            Vec3f point2 = {tangents[i].x,
                            tangents[i].y,
                            tangents[i].z,};

            glVertex3fv(&point1.x);
            glVertex3fv(&point2.x);
        }
        glEnd();
        // draw tangents of the homogenized curve
        glColor3f(0.5f, 0.0f, 0.5f);
        glBegin(GL_LINES);
        for (unsigned int i = 0; i < tangents.size(); ++i) {
            auto p = points[i];
            auto t = tangents[i];
            p = p / p.w;
            t = t / t.w;
            t = p + t;
            glVertex3fv(&p.x);
            t = (t - p).normalized() + p;
            glVertex3fv(&t.x);
        }
        glEnd();*/
    }
}

Vec3f setcolor(){
    float a = rand() / (float)RAND_MAX;
    float b = rand() / (float)RAND_MAX;
    float c = rand() / (float)RAND_MAX;

    Vec3f vec =  Vec3f(a,b,c);
    return vec;
}

#define RADPERDEG 0.0174533

#include "stdio.h"
#include "iostream"
#include "CurveRendering.h"
#include <cmath>
#include <GLUT/glut.h>
#include <BezierCurve.h>
#include <NURBSCurve.h>
#include <algorithm>

#define numberOfPoints 100


void drawBezier(BezierCurve &bezierCurve, Vec3f color) {
    std::pair<std::vector<Vec3f>, std::vector<Vec3f>> points = bezierCurve.evaluateCurve(numberOfPoints);
    int counter = 0;
    Vec3f testColor = Vec3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glColor3fv(&testColor.x);
    for (float i = 0.0; i <= 1.0; i += 1.0f / numberOfPoints) {
        std::vector<Vec3f> myPointArray = points.first;
        Vec3f myPoint = myPointArray[counter];
        glVertex3fv(&myPoint.x);
        counter++;
    }
    glVertex3fv(&bezierCurve.getControlPoints()[bezierCurve.getControlPoints().size() - 1].x);
    glEnd();
}

void drawBezierCtrlPolygon(const BezierCurve &bezierCurve, Vec3f color) {
    glBegin(GL_LINE_STRIP); //make line
    glColor3fv(&color.x); //color
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
        glColor3fv(&color.x);
        for (int i = 0; i < bezierCurve.getControlPoints().size(); i++) {
            Vec3f point = bezierCurve.getControlPoints()[i] / bezierCurve.getControlPoints()[i].z;
            glVertex3fv(&point.x);
        }
        glEnd();
    }
}

void drawNURBS(NURBSCurve &nurbsCurve, Vec3f color) {
    // TODO: draw NURBS curve
    // NOT homogenized
    // ===================================================================================


    // ===================================================================================
}

void drawNURBS_H(NURBSCurve &nurbsCurve, Vec3f color) {
    // TODO: draw NURBS curve
    // homogenized
    // ===================================================================================


    // ===================================================================================
}

void drawNURBSCtrlPolygon(const NURBSCurve &nurbsCurve, Vec3f color) {
    // TODO: implement the visualization of the
    // NOT homogenized
    // NURBS' control polygon (e.g. with GL_LINE_STRIP)
    // =========================================================================================================


    // =========================================================================================================
}

void drawNURBSCtrlPolygon_H(const NURBSCurve &nurbsCurve, Vec3f color) {
    // TODO: implement the visualization of the
    // homogenized
    // NURBS' control polygon (e.g. with GL_LINE_STRIP)
    // =========================================================================================================


    // =========================================================================================================
}

void renderBezier(BezierCurve &bezierCurve, Vec3f color) {
    auto pointsAndTangents = bezierCurve.evaluateCurve(size_t(100));
    if (bezierCurve.isRational()) {
        color = Vec3f(1.0f, 0.0f, 1.0f);
        drawRationalBezier(bezierCurve, color);
    }
    else{
        drawBezier(bezierCurve, color);
    }
}

void renderBezierEvaluation(BezierCurve &bezierCurve, float t) {
    Vec3f color = {1.0f, 1.0f, 1.0f};
    if (bezierCurve.getControlPoints().size() > 1) {
        bool rational = bezierCurve.isRational();
        auto twoBezierCurves = bezierCurve.separateCurveAt(t);

        glLineWidth(2.0f);

        // first partial curve cps
        if (rational)color = Vec3f(0.8f, 5.0f, 0.4f);
        else color = Vec3f(0.8f, 0.0f, 0.4f);
        drawBezierCtrlPolygon(twoBezierCurves.first, color);
        // second partial curve cps
        if (rational)color = Vec3f(0.4f, 5.0f, 0.8f);
        else color = Vec3f(0.4f, 0.0f, 0.8f);
        drawBezierCtrlPolygon(twoBezierCurves.second, color);

        glLineWidth(1.0f);
        // cps of the complete curve
        if (rational)color = Vec3f(0.3f, 0.2f, 0.7f);
        else color = Vec3f(0.3f, 0.7f, 0.7f);
        drawBezierCtrlPolygon(bezierCurve, color);

        glLineWidth(2.0f);
        if (bezierCurve.isRational()) {

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
        Vec3f color = Vec3f(1.0f, 0.8f, 0.0f);
        drawNURBS(nurbsCurve, color);
        color = Vec3f(0.8f, 1.0f, 0.0f);
        drawNURBS_H(nurbsCurve, color);
    }
}

void renderNURBSEvaluation(NURBSCurve &nurbsCurve, float t) {
    Vec3f color = Vec3f(1.0f, 1.0f, 1.0f);
    if (!nurbsCurve.isValidNURBS())
        return;

    auto pointsAndTangents = nurbsCurve.evaluateCurve(size_t(50));
    auto points = pointsAndTangents.first;
    auto tangents = pointsAndTangents.second;

    if (points.size() > 1 && nurbsCurve.getControlPoints().size() > 1) {

        // draw control polygon (x, y, w) not homogenized
        color = Vec3f(0.7f, 0.5f, 0.0f);
        drawNURBSCtrlPolygon(nurbsCurve, color);
        // draw control polygon (x/w, y/w, w=1) homogenized
        color = Vec3f(0.7f, 0.0f, 0.7f);
        drawNURBSCtrlPolygon_H(nurbsCurve, color);

        // draw tangents of the not homogenized curve
        glColor3f(0.5f, 0.35f, 0.0f);
        glBegin(GL_LINES);
        for (unsigned int i = 0; i < tangents.size(); ++i) {
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
        glEnd();
    }
}

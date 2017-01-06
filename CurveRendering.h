// ========================================================================= //
// Authors: Felix Schuwirth                                                  //
// mailto:felix.schuwirth@igd.fraunhofer.de                                  //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universit�t Darmstadt                                          //
// Fraunhoferstrasse 5                                                       //
// D-64283 Darmstadt, Germany                                                //
// ========================================================================= //

#ifndef CURVE_RENDERING_H
#define CURVE_RENDERING_H
#include "Vec3.h"

class BezierCurve;
class NURBSCurve;

// render evaluation information of the bezier curve wit parameter t of the half edge
float factorial(float n);void drawBernsteinPolynom(int i, int n);
float calcBernstein(int n, int i, float u);
float binCoefficient(int n, int i);

void drawBezier(BezierCurve &bezierCurve, Vec3f color);
void drawRationalBezier(BezierCurve &bezierCurve, Vec3f color);
void drawBezierCtrlPolygon(const BezierCurve &bezierCurve, Vec3f color);
void drawRationalBezierCtrlPolygon(const BezierCurve &bezierCurve, Vec3f color);

void drawNURBS(NURBSCurve &nurbsCurve, Vec3f color);
void drawNURBS_H(NURBSCurve &nurbsCurve, Vec3f color);
void drawNURBSCtrlPolygon(const NURBSCurve &nurbsCurve, Vec3f color);
void drawNURBSCtrlPolygon_H(const NURBSCurve &nurbsCurve, Vec3f color);


void renderBezier(BezierCurve &bezierCurve, Vec3f color);
void renderBezierEvaluation(BezierCurve &bezierCurve, float t);
void renderNURBS(NURBSCurve &nurbsCurve);
void renderNURBSEvaluation(NURBSCurve &nurbsCurve, float t);

#endif //

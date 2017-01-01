// ========================================================================= //
// Authors: Felix Schuwirth                                                  //
// mailto:felix.schuwirth@igd.fraunhofer.de                                  //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universität Darmstadt                                          //
// Fraunhoferstrasse 5                                                       //
// D-64283 Darmstadt, Germany                                                //
//                                                                           //
// Creation Date: 06.12.2016                                                 //
// Content: Simple and extendable openGL program offering                    //
//   * basic navigation and basic pipeline rendering                         //
// ========================================================================= //
#include "main.h"		// this header
#include "vector"
#include <stdlib.h>		// standard library
#include <cmath>		// fmod
#include <stdio.h>		// cout
#include <iostream>		// cout
#include <CurveRendering.h>

#define numberPoints 10
// ==============
// === BASICS ===
// ==============

std::vector<Vec3f> ctrlPts;

int main(int argc, char** argv)
{
    // initialize openGL window
    glutInit(&argc, argv);
    glutInitWindowPosition(300, 200);
    glutInitWindowSize(2400, 1500);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("TU Darmstadt, FSchuwirth");
    // link functions to certain openGL events
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);
    glutMouseFunc(mousePressed);
    glutMotionFunc(mouseMoved);
    glutKeyboardFunc(keyPressed);
    // further initializations
    setDefaults();
    createCurves();
    initializeGL();
    // activate main loop
    glutMainLoop();
    return 0;
}

void setDefaults()
{
    // scene Information
    transX = -1.0f;
    transY = -1.0f;
    transZ = -4.0f;
    angleX = 0.0f;
    angleY = 0.0f;
    // mouse information
    mouseX = 0;
    mouseY = 0;
    mouseButton = 0;
    activeBezier = 0;
    mouseSensitivy = 1.0f;
    evalParameter = 0.6f;
}

void initializeGL()
{
    // black screen
    glClearColor(0, 0, 0, 0);
    // enable depth buffer
    glEnable(GL_DEPTH_TEST);
    // Use Point Smoothing
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5.0f);
    glLineWidth(2.0f);
    // set shading model
    glShadeModel(GL_SMOOTH);
    // key bindings => cout
    coutHelp();
}

void createCurves()
{
    bezierCurves.clear();
    // TODO: create at least one bezier and one degree 2 quarter circle rational bezier curve
    // ==========================================================================


    // ==========================================================================
    for (auto &b : bezierCurves)
        std::cout << b << std::endl;

    nurbsCurves.clear();
    // TODO: set values to describe a degree 2 quarter circle in first quadrant, XY-plane
    // ==================================================================================


    // ==================================================================================
    for (auto &n : nurbsCurves)
        std::cout << n << std::endl;
}

void reshape(GLint width, GLint height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (float)width / (float)height, 0.1f, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// =================
// === RENDERING ===
// =================

void drawCS()
{
    glBegin(GL_LINES);
    // red X
    glColor3f(0.8f, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0.5, 0, 0);
    // green Y
    glColor3f(0, 0.8f, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.5, 0);
    // blue Z
    glColor3f(0, 0, 0.8f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 0.5);
    glEnd();
}

void fillArray()
{
    //creates control points
    Vec3f point0 = Vec3f(1.0, 0.0, 1.0);
    Vec3f point1 = Vec3f(1.0, 1.0, 1.0);
    Vec3f point2 = Vec3f(0.0, 2.0, 2.0);
    Vec3f point3 = Vec3f(-1.0, 1.0, 1.0);
    Vec3f point4 = Vec3f(-1.0, 0.0, 1.0);
    Vec3f point5 = Vec3f(-1.0, -1.0, 1.0);
    Vec3f point6 = Vec3f(0.0, -2.0, 2.0);
    Vec3f point7 = Vec3f(1.0, -1.0, 1.0);
    Vec3f point8 = Vec3f(1.0, 0.0, 1.0);

    ctrlPts.push_back(point0);
    ctrlPts.push_back(point1);
    ctrlPts.push_back(point2);
    ctrlPts.push_back(point3);
    ctrlPts.push_back(point4);
    ctrlPts.push_back(point5);
    ctrlPts.push_back(point6);
    ctrlPts.push_back(point7);
    ctrlPts.push_back(point8);
    /*for (float u = 0.0; u < 1; u += 0.5f)
    {
        ctrlPts.push_back(Vec3f(1 - pow(u, 2), 2 * u, 1 + pow(u, 2)));
    }*/
}

void drawObjects()
{
    Vec3f curveColor = Vec3f(0.1f, 0.1f, 0.1f);
    Vec3f ctrlPolygonCol = Vec3f(1.0f, 0.0f, 0.0f);
    for(unsigned int i = 0; i < bezierCurves.size(); i++)
    {
        renderBezier(bezierCurves[i], curveColor);
        curveColor = curveColor +  Vec3f(0.0f, 0.3f, 0.3f);
        ctrlPolygonCol = ctrlPolygonCol + Vec3f(0.0f, 0.5f, 0.0f);
        if(i == activeBezier)
        {
            renderBezierEvaluation(bezierCurves[i], evalParameter);
        }
    }
    for(unsigned int i = 0; i < nurbsCurves.size(); ++i)
    {
        renderNURBS(nurbsCurves[i]);
        if(i == activeNURBS)
            renderNURBSEvaluation(nurbsCurves[i], evalParameter);
    }
}

void renderScene()
{
    // clear and set camera
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // translate scene in viewing direction
    glTranslatef(transX, transY, transZ);
    // rotate scene
    glRotatef(angleX, 0.0f, 1.0f, 0.0f);
    glRotatef(angleY, 1.0f, 0.0f, 0.0f);
    // draw coordinate system without lighting
    glDisable(GL_LIGHTING);
    drawCS();
    drawObjects();
    // swap Buffers
    glFlush();
    glutSwapBuffers();
}

// =================
// === CALLBACKS ===
// =================

void keyPressed(unsigned char key, int x, int y)
{
    switch(key)
    {
    // esc => exit
        case 27:
            exit(0);
        break;
    // help file
        case 'h' :
        case 'H' :
            coutHelp();
            break;
            // reset view
        case 'r' :
        case 'R' :
            setDefaults();
            glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
            break;
        case 'a' :
        case 'A' :
            if(activeBezier <= bezierCurves.size() - 1)
            {
                activeBezier += 1;
            }
            else {
                activeBezier = 0;
            }
            std::cout <<"bezierCurves:" << bezierCurves.size() << " activeBezier: " << activeBezier << std::endl;
            glutPostRedisplay();
        case '+' :
            if(evalParameter < 1.0)
            {
                evalParameter += 0.01 ;
                glutPostRedisplay();    // use this whenever 3d data changed to redraw the scene
            }
            break;
        case '-' :
            if(evalParameter > 0)
            {
                evalParameter -= 0.01;
                glutPostRedisplay();    // use this whenever 3d data changed to redraw the scene
            }
            break;
        case 'f' :
        case 'F' : {
            fillArray();
            BezierCurve *myBezier = new BezierCurve(ctrlPts, true);
            bezierCurves.push_back(*myBezier);
            glutPostRedisplay();    // use this whenever 3d data changed to redraw the scene
            break;
        }
    // TODO: place custom functions on button evyents here to present your results
    // like changing the active Bbezier/NURBS curve (activeNURBS, activeBezier)
    // and varying the evaluation parameter (evalParameter) for the bezier curve
    // ==========================================================================


    // ==========================================================================
    }
}

void separateLast()
{
    std::pair<BezierCurve, BezierCurve> curves = bezierCurves[bezierCurves.size() - 1].separateCurveAt(0.5);
    bezierCurves.push_back(curves.first);
    bezierCurves.push_back(curves.second);
}

void mousePressed(int button, int state, int x, int y)
{
    mouseButton = button;
    mouseX = x;
    mouseY = y;
}

void mouseMoved(int x, int y)
{
    // rotate (cap angleY within [-85°, +85°])
    if(mouseButton == GLUT_LEFT_BUTTON)
    {
        angleX = fmod(angleX + (x - mouseX) * mouseSensitivy, 360.0f);
        angleY += (y - mouseY) * mouseSensitivy;
        if(angleY > 85) angleY = 85;
        if(angleY < -85) angleY = -85;
        glutPostRedisplay();
    }
    // zoom (here translation in z)
    if(mouseButton == GLUT_RIGHT_BUTTON)
    {
        transZ -= 0.2f * (y - mouseY) * mouseSensitivy;
        glutPostRedisplay();
    }
    // translation in xy
    if(mouseButton == GLUT_MIDDLE_BUTTON)
    {
        transX += 0.2f * (x - mouseX) * mouseSensitivy;
        transY -= 0.2f * (y - mouseY) * mouseSensitivy;
        glutPostRedisplay();
    }
    // update mouse for next relative movement
    mouseX = x;
    mouseY = y;
}

// ===============
// === VARIOUS ===
// ===============

void coutHelp()
{
    std::cout << std::endl;
    std::cout << "====== KEY BINDINGS ======" << std::endl;
    std::cout << "ESC: exit" << std::endl;
    std::cout << "H: show this (H)elp file" << std::endl;
    std::cout << "R: (R)eset view" << std::endl;
    std::cout << "F: create control points" << std::endl;
    std::cout << "'+': add 0.01 to evalParameter" << std::endl;
    std::cout << "'-': subtract 0.01 from evalParameter" << std::endl;
    // TODO: update help text according to your changes
    // ================================================


    // ================================================
    std::cout << "==========================" << std::endl;
    std::cout << std::endl;
}

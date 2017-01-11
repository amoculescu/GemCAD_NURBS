// ========================================================================= //
// Authors: Felix Schuwirth                                                  //
// mailto:felix.schuwirth@igd.fraunhofer.de                                  //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universit�t Darmstadt                                          //
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
#include "CurveRendering.h"

#define numberPoints 100
// ==============
// === BASICS ===
// ==============

std::vector<Vec3f> ctrlPts;
std::vector<Vec4f> ctrlPtsNurbs;
std::vector<float> knotVector;

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
    activeNURBS = 0;
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
    Vec3f point0 = Vec3f(1.0f, 1.0f, 1.0f);
    Vec3f point1 = Vec3f(2.0f, 3.0f, -3.0f);
    Vec3f point2 = Vec3f(4.0f, 6.0f, -1.0f);
    Vec3f point3 = Vec3f(7.0f, 4.0f, 2.0f);
    Vec3f point4 = Vec3f(10.0f, 0.0f, 5.0f);
    Vec3f point5 = Vec3f(11.0f, -2.0f, -3.0f);

    ctrlPts.push_back(point0);
    ctrlPts.push_back(point1);
    ctrlPts.push_back(point2);
    ctrlPts.push_back(point3);
    ctrlPts.push_back(point4);
    ctrlPts.push_back(point5);
}

void fillArrayCircle()
{
    Vec3f point0 = Vec3f(1.0f, 0.0f, 1.0f);
    Vec3f point1 = Vec3f(1.0f, 1.0f, 1.0f);
    Vec3f point2 = Vec3f(0.0f, 2.0f, 2.0f);
    Vec3f point3 = Vec3f(-1.0f, 1.0f, 1.0f);
    Vec3f point4 = Vec3f(-1.0f, 0.0f, 1.0f);
    Vec3f point5 = Vec3f(-1.0f, -1.0f, 1.0f);
    Vec3f point6 = Vec3f(0.0f, -2.0f, 2.0f);
    Vec3f point7 = Vec3f(1.0f, -1.0f, 1.0f);
    Vec3f point8 = Vec3f(1.0f, 0.0f, 1.0f);

    ctrlPts.push_back(point0);
    ctrlPts.push_back(point1);
    ctrlPts.push_back(point2);
    ctrlPts.push_back(point3);
    ctrlPts.push_back(point4);
    ctrlPts.push_back(point5);
    ctrlPts.push_back(point6);
    ctrlPts.push_back(point7);
    ctrlPts.push_back(point8);
}

void fillArrayNurbs()
{

	Vec4f point0 = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
	Vec4f point1 = Vec4f(2.0f, 4.0f, 1.0f, 2.0f);
	Vec4f point2 = Vec4f(3.0f, 9.0f, 1.0f, 3.0f);
	Vec4f point3 = Vec4f(4.0f, 5.0f, 1.0f, 2.0f);
	Vec4f point4 = Vec4f(5.0f, 10.0f, 1.0f, 2.0f);
	Vec4f point5 = Vec4f(6.0f, 1.0f, 1.0f, 1.0f);

	ctrlPtsNurbs.push_back(point0);
	ctrlPtsNurbs.push_back(point1);
	ctrlPtsNurbs.push_back(point2);
	ctrlPtsNurbs.push_back(point3);
	ctrlPtsNurbs.push_back(point4);
	ctrlPtsNurbs.push_back(point5);

	float knot0 = 0;
	float knot1 = 0;
	float knot2 = 0;
	float knot3 = 0.25;
	float knot4 = 0.5;
	float knot5 = 0.75;
	float knot6 = 1;
	float knot7 = 1;
	float knot8 = 1;

	knotVector.push_back(knot0);
	knotVector.push_back(knot1);
	knotVector.push_back(knot2);
	knotVector.push_back(knot3);
	knotVector.push_back(knot4);
	knotVector.push_back(knot5);
	knotVector.push_back(knot6);
	knotVector.push_back(knot7);
	knotVector.push_back(knot8);

}

void fillArrayNurbsCircle()
{
	// Kreis
	Vec4f point0 = Vec4f(1.0f, 0.0f, 0.0f, 1.0f);
	Vec4f point1 = Vec4f(1.0f, 1.0f, 0.0f, 0.7071f);
	Vec4f point2 = Vec4f(0.0f, 1.0f, 0.0f, 1.0f);
	Vec4f point3 = Vec4f(-1.0f, 1.0f, 0.0f, 0.7071f);
	Vec4f point4 = Vec4f(-1.0f, 0.0f, 0.0f, 1.0f);
	Vec4f point5 = Vec4f(-1.0f, -1.0f, 0.0f, 0.7071f);
	Vec4f point6 = Vec4f(0.0f, -1.0f, 0.0f, 1.0f);
	Vec4f point7 = Vec4f(1.0f, -1.0f, 0.0f, 0.7071f);
	Vec4f point8 = Vec4f(1.0f, 0.0f, 0.0f, 1.0f);

	ctrlPtsNurbs.push_back(point0);
	ctrlPtsNurbs.push_back(point1);
	ctrlPtsNurbs.push_back(point2);
	ctrlPtsNurbs.push_back(point3);
	ctrlPtsNurbs.push_back(point4);
	ctrlPtsNurbs.push_back(point5);
	ctrlPtsNurbs.push_back(point6);
	ctrlPtsNurbs.push_back(point7);
	ctrlPtsNurbs.push_back(point8);


	knotVector.push_back(0);
	knotVector.push_back(0);
	knotVector.push_back(0);
	knotVector.push_back(.25);
	knotVector.push_back(.25);
	knotVector.push_back(.5);
	knotVector.push_back(.5);
	knotVector.push_back(.75);
	knotVector.push_back(.75);
	knotVector.push_back(1);
	knotVector.push_back(1);
	knotVector.push_back(1);

}

void drawObjects()
{
    Vec3f curveColor = Vec3f(0.1f, 0.1f, 0.1f);
    Vec3f ctrlPolygonCol = Vec3f(1.0f, 0.0f, 0.0f);
    for(unsigned int i = 0; i < bezierCurves.size(); i++)
    {
        renderBezier(bezierCurves[i]);
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
        case '1':
            setKlickiBunti();
            break;
        case 'h' :
        case 'H' :
            coutHelp();
            break;
            // reset view
        case 'r' :
        case 'R' :
        {
            fillArrayCircle();
            BezierCurve *myBezier = new BezierCurve(ctrlPts, true);
            bezierCurves.push_back(*myBezier);
            ctrlPts.clear();
            glutPostRedisplay();    // use this whenever 3d data changed to redraw the scene
            break;
        }
        case 'a' :
        case 'A' :
            if(bezierCurves.size() > 0)
            {
                if (activeBezier < bezierCurves.size())
                {
                    activeBezier += 1;
                } else
                {
                    activeBezier = 0;
                }
            }
            if(nurbsCurves.size() > 0)
            {
                if(activeNURBS < nurbsCurves.size())
                {
                    activeNURBS += 1;
                }
                else
                {
                    activeNURBS = 0;
                }
            }
            glutPostRedisplay();
			break;
        case '+' :
            if(evalParameter < 1.0)
            {
                evalParameter += 0.01 ;
                glutPostRedisplay();    // use this whenever 3d data changed to redraw the scene
            }
            break;
        case '-' :
            if(evalParameter > 0.0)
            {
                evalParameter -= 0.01;
                glutPostRedisplay();    // use this whenever 3d data changed to redraw the scene
            }
            break;
        case 'b' :
        case 'B' : {
            fillArray();
            BezierCurve *myBezier = new BezierCurve(ctrlPts, false);
            bezierCurves.push_back(*myBezier);
			ctrlPts.clear();
            glutPostRedisplay();    // use this whenever 3d data changed to redraw the scene
            break;
        }
        case 'k':
		case 'K': {
			fillArrayNurbsCircle();
			NURBSCurve *circle = new NURBSCurve(ctrlPtsNurbs, knotVector, 2);
			nurbsCurves.push_back(*circle);
			glutPostRedisplay(); // use this whenever 3d data changed to redraw the scene
            knotVector.clear();
            ctrlPtsNurbs.clear();
			break;
		}
		case 'c':
		case 'C': {
            nurbsCurves.clear();
			bezierCurves.clear();
			ctrlPtsNurbs.clear();
			knotVector.clear();
            setDefaults();
            glutPostRedisplay(); // use this whenever 3d data changed to redraw the scene
			break;
        }
        case 'v':
        case 'V':
        {
            int pos;
            float knot;
            std::cout << "specify a knot in knotvector" << std::endl;
            std::cin >> pos;
            std::cout << "specify a new value for the knot" << std::endl;
            std::cin >> knot;
            nurbsCurves[activeNURBS].changeKnotVector(pos, knot);
            glutPostRedisplay();
            break;
        }
        case 'w':
        case 'W':
        {
            int pos;
            float weight;
            std::cout << "select a point" << std::endl;
            std::cin >> pos;
            std::cout << "specify a new weight" << std::endl;
            std::cin >> weight;
            nurbsCurves[activeNURBS].changeWeight(pos, weight);
            glutPostRedisplay();
            break;
        }
		case 'n':
		case 'N': {
			fillArrayNurbs();
			NURBSCurve *myNURBS = new NURBSCurve(ctrlPtsNurbs, knotVector, 2);
			nurbsCurves.push_back(*myNURBS);
			glutPostRedisplay();    // use this whenever 3d data changed to redraw the scene
            knotVector.clear();
            ctrlPtsNurbs.clear();
			break;
		}
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
    // rotate (cap angleY within [-85�, +85�])
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

    // TODO: update help text according to your changes
    // ================================================
	std::cout << "------ " << std::endl;
	std::cout << "B: draws a non rational Bezier Curve" << std::endl;
    std::cout << "R: draw circle with rational bezier curve" << std::endl;
    std::cout << "K: draws a cirlcle with nurbs Curve" << std::endl;
    std::cout << "N: nurbs curve" << std::endl;
    std::cout << "'+': add 0.01 to evalParameter" << std::endl;
	std::cout << "'-': subtract 0.01 from evalParameter" << std::endl;
	std::cout << "------ NURBS ------" << std::endl;
	std::cout << "'K': (K)reis - draws a circle" << std::endl;
	std::cout << "'N': (N)URBS - draws a simple example" << std::endl;
    // ================================================
    std::cout << "==========================" << std::endl;
    std::cout << std::endl;
}

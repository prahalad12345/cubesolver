#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <cstdio>
#include <algorithm>
#include <sstream>
//bahkrigandchod
using namespace std;

void keyInput(unsigned char key, int x, int y)
{
    vector< vector < char > > copycube;
    copycube=cube;
    
    switch (key)
    {
    case 'j':
        Xangle += 2;
        glutPostRedisplay();
        break;
    case 'k':
        Xangle -= 2;
        glutPostRedisplay();
        break;
    case 'l':
        Yangle += 2;
        glutPostRedisplay();
        break;
    case 'b':
        Yangle -= 2;
        glutPostRedisplay();
        break;
    case 'm':
        Zangle -= 2;
        glutPostRedisplay();
        break;
    case 'n':
        Zangle += 2;
        glutPostRedisplay();
        break;
    case 'q':
        movee=0;
        break;
    case 'w':
        movee=1;
        break;
    case 'e':
        movee=2;
        break;
    case 'a':
        movee=3;
        break;
    case 's':
        movee=4;
        break;
    case 'd':
        movee=5;
        break;
    case '3':
        if (a > 0.0) a -= 0.05;
        glutPostRedisplay();
        break;
    case '4':
        if (a < 1.0) a += 0.05;
        glutPostRedisplay();
        break;
    case '5':
        if (d > 0.0) d -= 0.05;
        glutPostRedisplay();
        break;
    /*case '6':
        if (d < 1.0) d += 0.05;
        glutPostRedisplay();
        break;
    case '7':
        if (s > 0.0) s -= 0.05;
        glutPostRedisplay();
        break;*/
    case '8':
        if (s < 1.0) s += 0.05;
        glutPostRedisplay();
    case '9':
        if (e > 0.0) e -= 0.05;
        glutPostRedisplay();
        break;
    case '0':
        if (e < 1.0) e+= 0.05;
        glutPostRedisplay();
        break;
    case '1':
        if (h < 128.0) h += 1.0;
        glutPostRedisplay();
        break;
    // u is clockwise
    case 'u':
        // Left face clockwise
        moveanticlockwise(copycube,movee);
        cube=copycube;
         glutPostRedisplay();
        break;
    case 'o':
                // Left face clockwise
        moveclockwise(copycube,movee);
        cube=copycube;
        glutPostRedisplay();
        break;
    case 'g':
        solver();
        glutPostRedisplay();
        break;
    case '2':
        availableopt();
        break;
    case '6':
        scancube();
        glutPostRedisplay();
        break;
    case '7':
        scaninputkociemba();
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}
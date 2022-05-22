///////////////////////////////////
// Cube Modelling,Scanner and Solver
//
// Group:Prahalad Vijaykumar,Anish Natekar,Aditya Koshti
///////////////////////////////////
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <cstdio>
#include <algorithm>
#include <sstream>

using namespace std;

// Globals.
static float a = 1.0;  // Blue ambient reflectance.
static float d = 1.0;  // Blue diffuse reflectance.
static float s = 1.0;  // White specular reflectance.
static float h = 50.0; // Shininess.
static float e = 0.0;  // Blue emittance.

vector<vector<char> > cube;     //cube modelling
map<char, vector<float> > colors;//color mapping
vector<vector<int> > offset;    //the rendering of face from the center of the cube face
vector<char> direction;         //direction keeps track of the move to be done it stores either clockwise ='o' or anticlockwise='u' 
vector<int> movevector;         //move vector stores the solution for the cube moves
string res, moves;
int movee = 0;                  //movee has 6 options rotate up or down or left or right or back or front
// Drawing routine.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate scene.

void createFaces()
{
    /*
     createFaces() models the whole cube. places the stickers on the cube based cube vector state
     material is defined instead of color to provide the lighting effect for a more glossier finishl
    */
    // defining the material property vectors for green
    float matAmbGreen[] = {0.0, a, 0.0, 1.0};
    float matDifGreen[] = {0.0, d, 0.0, 1.0};
    float matSpec[] = {s, s, s, 1.0};
    float matShine[] = {h};
    float matEmission[] = {0.0, 0.0, e, 1.0};

    // defining the material property vector for red
    float matAmbRed[] = {a, 0.0, 0.0, 1.0};
    float matDifRed[] = {d, 0.0, 0.0, 1.0};

    // defining the material property vector for white
    float matAmbWhite[] = {a, a, a, 1.0};
    float matDifWhite[] = {d, d, d, 1.0};

    // defning the material property vector for orange
    float matAmbOrange[] = {1.0, 0.15, 0.0, 1.0};
    float matDifOrange[] = {1.0, 0.15, 0.0, 1.0};

    // defining the material property vector for yellow
    float matAmbYellow[] = {a, a, 0.0, 1.0};
    float matDifYellow[] = {d, d, 0.0, 1.0};

    // defining the material property vector for blue
    float matAmbBlue[] = {0.0, 0.0, a, 1.0};
    float matDifBlue[] = {0.0, 0.0, d, 1.0};

    // reading the cube vector containing the state of the cube and drawing the stickers of each faces according to the colours in the cube vector
    // starting with UP face (Up face has Red at the center)
    for (int i = 0; i < 9; i++)
    {
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslated(offset[i][0], 15, offset[i][1]);
        glScalef(1, 0.1, 1);
        //placing the sticker based on the value of the element in the cube on the upper side at some from the center of the face
        // Selecting the material of the stickers depending on their colour. Color is stored in the cube vector
        switch (cube[0][i])
        {
        case 'W':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbWhite);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifWhite);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'R':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbRed);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifRed);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'B':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbBlue);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifBlue);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'Y':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbYellow);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifYellow);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'O':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbOrange);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifOrange);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'G':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbGreen);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifGreen);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        }
        glutSolidCube(8);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    // RIGHT side of the cube is rendering now (The right side has green at the center)
    for (int i = 0; i < 9; i++)
    {
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslated(15, offset[i][1], offset[i][0]);
        glScalef(0.1, 1, 1);
        //choosing the material property based on the colour of the sticker
        switch (cube[1][i])
        {
        case 'W':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbWhite);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifWhite);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'R':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbRed);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifRed);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'B':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbBlue);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifBlue);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'Y':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbYellow);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifYellow);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'O':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbOrange);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifOrange);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'G':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbGreen);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifGreen);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        }
        glutSolidCube(8);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    // FRONT side of the cube is being rendered (The front has white at the center)
    for (int i = 0; i < 9; i++)
    {
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslated(offset[i][0], offset[i][1], -15);
        glScalef(1, 1, 0.1);
        //placing the value of the cube based on the value of the cube matrix at the front
        switch (cube[2][i])
        {
        case 'W':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbWhite);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifWhite);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'R':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbRed);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifRed);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'B':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbBlue);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifBlue);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'Y':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbYellow);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifYellow);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'O':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbOrange);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifOrange);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'G':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbGreen);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifGreen);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        }

        glutSolidCube(8);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    // DOWN side of the cube is being rendered (The down side has Orange at the center)
    for (int i = 0; i < 9; i++)
    {
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslated(offset[i][0], -15, -offset[i][1]);
        glScalef(1, 0.1, 1);
        //placing the value of the cube based on the value of the cube matrix at the down
        switch (cube[3][i])
        {
        case 'W':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbWhite);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifWhite);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'R':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbRed);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifRed);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'B':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbBlue);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifBlue);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'Y':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbYellow);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifYellow);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'O':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbOrange);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifOrange);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'G':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbGreen);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifGreen);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        }

        glutSolidCube(8);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    // LEFT side of the cube is being rendered (Left side has blue at the center)
    for (int i = 0; i < 9; i++)
    {
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslated(-15, offset[i][1], -offset[i][0]);
        glScalef(0.1, 1, 1);
        //placing the value of the cube based on the value of the cube matrix at the left
        switch (cube[4][i])
        {
        case 'W':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbWhite);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifWhite);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'R':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbRed);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifRed);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'B':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbBlue);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifBlue);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'Y':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbYellow);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifYellow);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'O':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbOrange);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifOrange);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'G':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbGreen);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifGreen);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        }

        glutSolidCube(8);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    // BACK side of the cube is being rendered (back side has color yellow)
    for (int i = 0; i < 9; i++)
    {
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslated(-offset[i][0], offset[i][1], 15);
        glScalef(1, 1, 0.1);
        //placing the value of the cube based on the value of the cube matrix at the back
        switch (cube[5][i])
        {
        case 'W':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbWhite);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifWhite);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'R':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbRed);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifRed);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'B':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbBlue);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifBlue);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'Y':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbYellow);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifYellow);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'O':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbOrange);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifOrange);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        case 'G':
            glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbGreen);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifGreen);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
            glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
            break;
        }

        glutSolidCube(8);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
}

// draw scene will call all functions to render the whole cube object and lighting
void drawScene(void)
{
    // Light position vectors
    float lightPos0[] = {30.0, 30.0, -30.0, 1.0};
    float lightPos1[] = {-30.0, -30.0, -30.0, 1.0};

    // material property vector for black
    float matAmbBlack[] = {0.1, 0.1, 0.1, 1.0};
    float matDifBlack[] = {0.1, 0.1, 0.1, 1.0};
    float matSpec[] = {s, s, s, 1.0};
    float matShine[] = {h};
    float matEmission[] = {0.0, 0.0, e, 1.0};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(Xangle, 1.0, 0.0, 0.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glDepthFunc(GL_LESS);
    glDisable(GL_LIGHTING);

    // Light0 and its sphere positioned.
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(0.05, 8, 8);
    glPopMatrix();

    // Light1 and its sphere positioned.
    glPushMatrix();
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glTranslatef(lightPos1[0], lightPos1[1], lightPos1[2]);
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(0.05, 8, 8);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    // defining the material properties for black colour
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbBlack);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifBlack);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

    //modelling the black cube
    glutSolidCube(29.9);
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();
    //modelling the faces
    createFaces();
    glFlush();
    glutSwapBuffers();
}

void scancube()
{
    FILE *fp;
    string calcube = "python3 colorreader.py";
    int sys1 = system(calcube.c_str());
    //the above line calls the coloreader code which is used to extract each face of the cube
    //1)upper 2)right 3)front 4)down 5)left 6)back
    
    fp = fopen("input.txt", "r");
    char res[300];
    fscanf(fp, "%s", res);

    //arrange the string for passing it efficiently to the kociemba algorithm and for showing the cube in opengl effectively
    string s = res;
    swap(s[0], s[2]);
    swap(s[3], s[5]);
    swap(s[6], s[8]);

    swap(s[18], s[20]);
    swap(s[21], s[23]);
    swap(s[24], s[26]);

    swap(s[9], s[11]);
    swap(s[12], s[14]);
    swap(s[15], s[17]);

    swap(s[36], s[38]);
    swap(s[39], s[41]);
    swap(s[42], s[44]);

    swap(s[27], s[29]);
    swap(s[30], s[32]);
    swap(s[33], s[35]);

    swap(s[45], s[47]);
    swap(s[48], s[50]);
    swap(s[51], s[53]);

    for (int i = 9; i < 18; i++)
        swap(s[i], s[27 + i]);
    
    //placing the string obtained in the cube to show the string in opengl
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cube[i][j] = s[i * 9 + j];
        }
    }
}

// Initialization routine.
void setup(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    // define light sources over here
    float lightAmb[] = {0.0, 0.0, 0.0, 1.0};
    float lightDifAndSpec0[] = {1.0, 1.0, 1.0, 1.0};
    float lightDifAndSpec1[] = {1.0, 1.0, 1.0, 1.0};
    float globAmb[] = {0.2, 0.2, 0.2, 1.0};
    // defining the two light sources 
    //light source.
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);

    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec0);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    // light sources definition end
    // Cull back faces
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void solver()
{
    FILE *fp;
    /*cube = {
      {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},	// UP - Red
      {'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},	// RIGHT - Green
      {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},	// FRONT - White
      {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},	// DOWN - Orange
      {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'},	// LEFT - Blue
      {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'}   // Back - Yellow
      };
      */
    string addfile = "touch input2.txt";
    int sys2 = system(addfile.c_str());
    string s = "";

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (cube[i][j] == 'R')
                s += "U";
            else if (cube[i][j] == 'G')
                s += "L";
            else if (cube[i][j] == 'W')
                s += "F";
            else if (cube[i][j] == 'O')
                s += "D";
            else if (cube[i][j] == 'B')
                s += "R";
            else
                s += "B";
        }
    }
    //generating the kociemba string
    swap(s[0], s[2]);
    swap(s[3], s[5]);
    swap(s[6], s[8]);

    swap(s[18], s[20]);
    swap(s[21], s[23]);
    swap(s[24], s[26]);

    swap(s[9], s[11]);
    swap(s[12], s[14]);
    swap(s[15], s[17]);

    swap(s[36], s[38]);
    swap(s[39], s[41]);
    swap(s[42], s[44]);

    swap(s[27], s[29]);
    swap(s[30], s[32]);
    swap(s[33], s[35]);

    swap(s[45], s[47]);
    swap(s[48], s[50]);
    swap(s[51], s[53]);

    for (int i = 9; i < 18; i++)
        swap(s[i], s[27 + i]);
    //swapping left faces and right faces for the kociemba alteration
    for (int i = 0; i < 54; i++)
    {
        if (s[i] == 'L')
            s[i] = 'R';
        else if (s[i] == 'R')
            s[i] = 'L';
    }

    fp = fopen("input2.txt", "w");
    fprintf(fp, "%s", s.c_str());
    fclose(fp);
    string compile = "python3 solver.py";
    //running the solver code in python 
    int sys3 = system(compile.c_str());
    FILE *fp2;
    fp2 = fopen("output.txt", "r");
    char res[50000];
    //read the string or the solution which is done by kociemba in the python code
    while (fscanf(fp2, "%s", res) != EOF)
    {
        //
        string s = res;
        if (s.length() == 1)
        {
            direction.push_back('o');
            if (s[0] == 'R')
                movevector.push_back(0);
            if (s[0] == 'L')
                movevector.push_back(1);
            if (s[0] == 'U')
                movevector.push_back(2);
            if (s[0] == 'D')
                movevector.push_back(3);
            if (s[0] == 'F')
                movevector.push_back(4);
            if (s[0] == 'B')
                movevector.push_back(5);
        }
        else
        {
            if (s[1] == '2')
            {
                direction.push_back('o');
                direction.push_back('o');
                for (int i = 0; i < 2; i++)
                {
                    if (s[0] == 'R')
                        movevector.push_back(0);
                    if (s[0] == 'L')
                        movevector.push_back(1);
                    if (s[0] == 'U')
                        movevector.push_back(2);
                    if (s[0] == 'D')
                        movevector.push_back(3);
                    if (s[0] == 'F')
                        movevector.push_back(4);
                    if (s[0] == 'B')
                        movevector.push_back(5);
                }
            }
            else
            {
                direction.push_back('u');
                if (s[0] == 'R')
                    movevector.push_back(0);
                if (s[0] == 'L')
                    movevector.push_back(1);
                if (s[0] == 'U')
                    movevector.push_back(2);
                if (s[0] == 'D')
                    movevector.push_back(3);
                if (s[0] == 'F')
                    movevector.push_back(4);
                if (s[0] == 'B')
                    movevector.push_back(5);
            }
        }
    }

    for (int i = 0; i < direction.size(); i++)
    {
        cout << direction[i] << " " << movevector[i] << endl;
    }
}

void scaninputkociemba()
{
    FILE *fp = fopen("input.txt", "r");
    char res[300];
    fscanf(fp, "%s", res);
    //extracts any previously scanned cube 
    string s = res;
    swap(s[0], s[2]);
    swap(s[3], s[5]);
    swap(s[6], s[8]);

    swap(s[18], s[20]);
    swap(s[21], s[23]);
    swap(s[24], s[26]);

    swap(s[9], s[11]);
    swap(s[12], s[14]);
    swap(s[15], s[17]);

    swap(s[36], s[38]);
    swap(s[39], s[41]);
    swap(s[42], s[44]);

    swap(s[27], s[29]);
    swap(s[30], s[32]);
    swap(s[33], s[35]);

    swap(s[45], s[47]);
    swap(s[48], s[50]);
    swap(s[51], s[53]);

    for (int i = 9; i < 18; i++)
        swap(s[i], s[27 + i]);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cube[i][j] = s[i * 9 + j];
        }
    }
}
// Function to make anticlockwise rotations in the cube matrix
void moveanticlockwise(vector<vector<char> > &copycube, int movee)
{
    //anticlockwise
    if (movee == 0)
    {
        // Face Transformation
        copycube[4][6] = cube[4][8];
        copycube[4][3] = cube[4][7];
        copycube[4][0] = cube[4][6];
        copycube[4][7] = cube[4][5];
        copycube[4][1] = cube[4][3];
        copycube[4][8] = cube[4][2];
        copycube[4][5] = cube[4][1];
        copycube[4][2] = cube[4][0];
        // Side Transformation
        // Up to Front
        copycube[2][0] = cube[0][0];
        copycube[2][3] = cube[0][3];
        copycube[2][6] = cube[0][6];
        // Front to Down
        copycube[3][0] = cube[2][0];
        copycube[3][3] = cube[2][3];
        copycube[3][6] = cube[2][6];
        // Down to Back
        copycube[5][8] = cube[3][0];
        copycube[5][5] = cube[3][3];
        copycube[5][2] = cube[3][6];
        // Back to Up
        copycube[0][0] = cube[5][8];
        copycube[0][3] = cube[5][5];
        copycube[0][6] = cube[5][2];
    }
    else if (movee == 1)
    {
        // Face Transformation
        copycube[1][6] = cube[1][8];
        copycube[1][3] = cube[1][7];
        copycube[1][0] = cube[1][6];
        copycube[1][7] = cube[1][5];
        copycube[1][1] = cube[1][3];
        copycube[1][8] = cube[1][2];
        copycube[1][5] = cube[1][1];
        copycube[1][2] = cube[1][0];
        // Side Transformation
        // Back to Up
        copycube[5][6] = cube[0][2];
        copycube[5][3] = cube[0][5];
        copycube[5][0] = cube[0][8];
        // Up to Front
        copycube[0][2] = cube[2][2];
        copycube[0][5] = cube[2][5];
        copycube[0][8] = cube[2][8];
        // Front to down
        copycube[2][2] = cube[3][2];
        copycube[2][5] = cube[3][5];
        copycube[2][8] = cube[3][8];
        // Down to Back
        copycube[3][8] = cube[5][0];
        copycube[3][5] = cube[5][3];
        copycube[3][2] = cube[5][6];
    }
    else if (movee == 2)
    {
        /*Face Transformation*/
        copycube[0][6] = cube[0][8];
        copycube[0][3] = cube[0][7];
        copycube[0][0] = cube[0][6];
        copycube[0][7] = cube[0][5];
        copycube[0][1] = cube[0][3];
        copycube[0][8] = cube[0][2];
        copycube[0][5] = cube[0][1];
        copycube[0][2] = cube[0][0];
        // end Face
        copycube[4][0] = cube[2][0];
        copycube[4][1] = cube[2][1];
        copycube[4][2] = cube[2][2];

        copycube[2][0] = cube[1][0];
        copycube[2][1] = cube[1][1];
        copycube[2][2] = cube[1][2];

        copycube[1][0] = cube[5][0];
        copycube[1][1] = cube[5][1];
        copycube[1][2] = cube[5][2];

        copycube[5][0] = cube[4][0];
        copycube[5][1] = cube[4][1];
        copycube[5][2] = cube[4][2];
    }
    else if (movee == 3)
    {
        /*Face Transformation*/
        copycube[3][6] = cube[3][8];
        copycube[3][3] = cube[3][7];
        copycube[3][0] = cube[3][6];
        copycube[3][7] = cube[3][5];
        copycube[3][1] = cube[3][3];
        copycube[3][8] = cube[3][2];
        copycube[3][5] = cube[3][1];
        copycube[3][2] = cube[3][0];
        // end Face

        copycube[2][6] = cube[4][6];
        copycube[2][7] = cube[4][7];
        copycube[2][8] = cube[4][8];
        copycube[1][6] = cube[2][6];
        copycube[1][7] = cube[2][7];
        copycube[1][8] = cube[2][8];
        copycube[5][6] = cube[1][6];
        copycube[5][7] = cube[1][7];
        copycube[5][8] = cube[1][8];
        copycube[4][6] = cube[5][6];
        copycube[4][7] = cube[5][7];
        copycube[4][8] = cube[5][8];
    }
    else if (movee == 4)
    {
        // ok
        copycube[2][0] = cube[2][6];
        copycube[2][1] = cube[2][3];
        copycube[2][2] = cube[2][0];
        copycube[2][3] = cube[2][7];
        copycube[2][5] = cube[2][1];
        copycube[2][6] = cube[2][8];
        copycube[2][7] = cube[2][5];
        copycube[2][8] = cube[2][2];

        copycube[3][2] = cube[1][0];
        copycube[3][1] = cube[1][3];
        copycube[3][0] = cube[1][6];

        copycube[1][6] = cube[0][8];
        copycube[1][3] = cube[0][7];
        copycube[1][0] = cube[0][6];

        copycube[4][2] = cube[3][0];
        copycube[4][5] = cube[3][1];
        copycube[4][8] = cube[3][2];

        copycube[0][8] = cube[4][2];
        copycube[0][7] = cube[4][5];
        copycube[0][6] = cube[4][8];
    }
    else if (movee == 5)
    {
        copycube[5][6] = cube[5][8];
        copycube[5][3] = cube[5][7];
        copycube[5][7] = cube[5][5];
        copycube[5][8] = cube[5][2];
        copycube[5][5] = cube[5][1];
        copycube[5][0] = cube[5][6];
        copycube[5][1] = cube[5][3];
        copycube[5][2] = cube[5][0];

        // ok
        copycube[0][0] = cube[1][2];
        copycube[0][1] = cube[1][5];
        copycube[0][2] = cube[1][8];
        // ok
        copycube[4][0] = cube[0][2];
        copycube[4][3] = cube[0][1];
        copycube[4][6] = cube[0][0];
        // ok
        copycube[3][8] = cube[4][6];
        copycube[3][7] = cube[4][3];
        copycube[3][6] = cube[4][0];
        // ok
        copycube[1][2] = cube[3][8];
        copycube[1][5] = cube[3][7];
        copycube[1][8] = cube[3][6];
    }
}
// function to make clockwise rotations on the cube matrix
void moveclockwise(vector<vector<char> > &copycube, int movee)
{
    //clockwise rotation
    if (movee == 0)
    {
        // Face Transformation
        copycube[4][6] = cube[4][0];
        copycube[4][3] = cube[4][1];
        copycube[4][0] = cube[4][2];
        copycube[4][7] = cube[4][3];
        copycube[4][1] = cube[4][5];
        copycube[4][8] = cube[4][6];
        copycube[4][5] = cube[4][7];
        copycube[4][2] = cube[4][8];
        // Side Transformation
        // Up to Front
        copycube[0][0] = cube[2][0];
        copycube[0][3] = cube[2][3];
        copycube[0][6] = cube[2][6];
        // Front to Down
        copycube[2][0] = cube[3][0];
        copycube[2][3] = cube[3][3];
        copycube[2][6] = cube[3][6];
        // Down to Back
        copycube[3][0] = cube[5][8];
        copycube[3][3] = cube[5][5];
        copycube[3][6] = cube[5][2];
        // Back to Up
        copycube[5][8] = cube[0][0];
        copycube[5][5] = cube[0][3];
        copycube[5][2] = cube[0][6];
    }
    else if (movee == 1)
    {
        // Face Transformation
        copycube[1][6] = cube[1][0];
        copycube[1][3] = cube[1][1];
        copycube[1][0] = cube[1][2];
        copycube[1][7] = cube[1][3];
        copycube[1][1] = cube[1][5];
        copycube[1][8] = cube[1][6];
        copycube[1][5] = cube[1][7];
        copycube[1][2] = cube[1][8];
        // Side Transformation
        // Back to Up
        copycube[0][2] = cube[5][6];
        copycube[0][5] = cube[5][3];
        copycube[0][8] = cube[5][0];
        // Up to Front
        copycube[2][2] = cube[0][2];
        copycube[2][5] = cube[0][5];
        copycube[2][8] = cube[0][8];
        // Front to down
        copycube[3][2] = cube[2][2];
        copycube[3][5] = cube[2][5];
        copycube[3][8] = cube[2][8];
        // Down to Back
        copycube[5][0] = cube[3][8];
        copycube[5][3] = cube[3][5];
        copycube[5][6] = cube[3][2];
    }
    else if (movee == 2)
    {
        /*Face Transformation*/
        copycube[0][6] = cube[0][0];
        copycube[0][3] = cube[0][1];
        copycube[0][0] = cube[0][2];
        copycube[0][7] = cube[0][3];
        copycube[0][1] = cube[0][5];
        copycube[0][8] = cube[0][6];
        copycube[0][5] = cube[0][7];
        copycube[0][2] = cube[0][8];
        // end Face
        copycube[2][0] = cube[4][0];
        copycube[2][1] = cube[4][1];
        copycube[2][2] = cube[4][2];

        copycube[1][0] = cube[2][0];
        copycube[1][1] = cube[2][1];
        copycube[1][2] = cube[2][2];

        copycube[5][0] = cube[1][0];
        copycube[5][1] = cube[1][1];
        copycube[5][2] = cube[1][2];

        copycube[4][0] = cube[5][0];
        copycube[4][1] = cube[5][1];
        copycube[4][2] = cube[5][2];
    }
    else if (movee == 3)
    {
        /*Face Transformation*/
        /*Face Transformation*/
        copycube[3][6] = cube[3][0];
        copycube[3][3] = cube[3][1];
        copycube[3][0] = cube[3][2];
        copycube[3][7] = cube[3][3];
        copycube[3][1] = cube[3][5];
        copycube[3][8] = cube[3][6];
        copycube[3][5] = cube[3][7];
        copycube[3][2] = cube[3][8];
        // end Face

        copycube[4][6] = cube[2][6];
        copycube[4][7] = cube[2][7];
        copycube[4][8] = cube[2][8];

        copycube[2][6] = cube[1][6];
        copycube[2][7] = cube[1][7];
        copycube[2][8] = cube[1][8];

        copycube[1][6] = cube[5][6];
        copycube[1][7] = cube[5][7];
        copycube[1][8] = cube[5][8];

        copycube[5][6] = cube[4][6];
        copycube[5][7] = cube[4][7];
        copycube[5][8] = cube[4][8];
    }
    else if (movee == 4)
    {
        // ok
        copycube[2][0] = cube[2][2];
        copycube[2][1] = cube[2][5];
        copycube[2][2] = cube[2][8];
        copycube[2][3] = cube[2][1];
        copycube[2][5] = cube[2][7];
        copycube[2][6] = cube[2][0];
        copycube[2][7] = cube[2][3];
        copycube[2][8] = cube[2][6];

        copycube[1][0] = cube[3][2];
        copycube[1][3] = cube[3][1];
        copycube[1][6] = cube[3][0];

        copycube[0][8] = cube[1][6];
        copycube[0][7] = cube[1][3];
        copycube[0][6] = cube[1][0];

        copycube[3][0] = cube[4][2];
        copycube[3][1] = cube[4][5];
        copycube[3][2] = cube[4][8];

        copycube[4][2] = cube[0][8];
        copycube[4][5] = cube[0][7];
        copycube[4][8] = cube[0][6];
    }
    else if (movee == 5)
    {
        copycube[5][6] = cube[5][0];
        copycube[5][3] = cube[5][1];
        copycube[5][7] = cube[5][3];
        copycube[5][8] = cube[5][6];
        copycube[5][5] = cube[5][7];
        copycube[5][0] = cube[5][2];
        copycube[5][1] = cube[5][5];
        copycube[5][2] = cube[5][8];

        // ok
        copycube[1][2] = cube[0][0];
        copycube[1][5] = cube[0][1];
        copycube[1][8] = cube[0][2];
        // ok
        copycube[0][2] = cube[4][0];
        copycube[0][1] = cube[4][3];
        copycube[0][0] = cube[4][6];
        // ok
        copycube[4][6] = cube[3][8];
        copycube[4][3] = cube[3][7];
        copycube[4][0] = cube[3][6];
        // ok
        copycube[3][8] = cube[1][2];
        copycube[3][7] = cube[1][5];
        copycube[3][6] = cube[1][8];
    }
}

void availableopt()
{
    //available option reads the output.txt file which is the solution of the cube
    //implement the motion of the cube on pressing the key 2
    //it'll directly move the sides of the cube
    if (direction.size() == 0)
    {
        cout << "Already solved" << endl;
        return;
    }
    char rotation = direction[0];
    direction.erase(direction.begin());

    vector<vector<char> > copycube;
    copycube = cube;

    movee = movevector[0];
    movevector.erase(movevector.begin());
    if (rotation == 'u')
    {
        // Left face clockwise
        moveanticlockwise(copycube, movee);
        cube = copycube;
        glutPostRedisplay();
    }
    else if (rotation == 'o')
    {
        // Left face clockwise
        moveclockwise(copycube, movee);
        cube = copycube;
        glutPostRedisplay();
    }
}

void keyInput(unsigned char key, int x, int y)
{
    vector<vector<char> > copycube;
    copycube = cube;

    switch (key)
    {
    case 'j':
        //x axis rotation
        Xangle += 2;
        glutPostRedisplay();
        break;
    case 'k':
        //x axis rotation 
        Xangle -= 2;
        glutPostRedisplay();
        break;
    case 'l':
        //y axis rotation
        Yangle += 2;
        glutPostRedisplay();
        break;
    case 'b':
        //y axis rotation
        Yangle -= 2;
        glutPostRedisplay();
        break;
    case 'm':
        //z axis rotation
        Zangle -= 2;
        glutPostRedisplay();
        break;
    case 'n':
        //z axis rotation
        Zangle += 2;
        glutPostRedisplay();
        break;
    case 'q':
        //specify right to rotate
        movee = 0;
        break;
    case 'w':
        //specify left to rotate
        movee = 1;
        break;
    case 'e':
        //specifyy up to rotate
        movee = 2;
        break;
    case 'a':
        //specify down to rotate
        movee = 3;
        break;
    case 's':
        //specify front to rotate
        movee = 4;
        break;
    case 'd':
        //back to be rotated
        movee = 5;
        break;
    case '3':
        if (a > 0.0)
            a -= 0.05;
        glutPostRedisplay();
        break;
    case '4':
        if (a < 1.0)
            a += 0.05;
        glutPostRedisplay();
        break;
    case '5':
        if (d > 0.0)
            d -= 0.05;
        glutPostRedisplay();
        break;
    case '1':
        if (d < 1.0) d += 0.05;
        glutPostRedisplay();
        break;
    case '8':
        if (s < 1.0)
            s += 0.05;
        glutPostRedisplay();
    // u is clockwise
    case 'u':
        // Left face clockwise
        moveanticlockwise(copycube, movee);
        cube = copycube;
        glutPostRedisplay();
        break;
    case 'o':
        // Left face clockwise
        moveclockwise(copycube, movee);
        cube = copycube;
        glutPostRedisplay();
        break;
    case 'g':
        solver();
        glutPostRedisplay();
        break;
    case '2':
        //solves the cube using the kocimeba algorithm
        availableopt();
        break;
    case '6':
        //scans the cube using opencv
        scancube();
        glutPostRedisplay();
        break;
    case '7':
        //record a previous recorded cube
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

// Main routine.
int main(int argc, char **argv)
{
    //initializing the cube
    cube.resize(6);
    char arr[6] = {'R', 'G', 'W', 'O', 'B', 'Y'};
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cube[i].push_back(arr[i]);
        }
    }
    offset.resize(9);
    offset[0].push_back(-10);
    offset[0].push_back(10);
    offset[1].push_back(0);
    offset[1].push_back(10);
    offset[2].push_back(10);
    offset[2].push_back(10);
    offset[3].push_back(-10);
    offset[3].push_back(0);
    offset[4].push_back(0);
    offset[4].push_back(0);
    offset[5].push_back(10);
    offset[5].push_back(0);
    offset[6].push_back(-10);
    offset[6].push_back(-10);
    offset[7].push_back(0);
    offset[7].push_back(-10);
    offset[8].push_back(10);
    offset[8].push_back(-10);
    /*cube = {
    {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},	// UP
    {'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},	// RIGHT
    {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},	// FRONT
    {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},	// DOWN
    {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'},	// LEFT
    {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'}   // Back
    };
    */
   //defining the color of the cube
    colors['R'].push_back(1.0);
    colors['R'].push_back(0.0);
    colors['R'].push_back(0.0);
    colors['G'].push_back(0.0);
    colors['G'].push_back(1.0);
    colors['G'].push_back(0.0);
    colors['B'].push_back(0.0);
    colors['B'].push_back(0.0);
    colors['B'].push_back(1.0);
    colors['W'].push_back(1.0);
    colors['W'].push_back(1.0);
    colors['W'].push_back(1.0);
    colors['O'].push_back(1.0);
    colors['O'].push_back(0.65);
    colors['O'].push_back(0.0);
    colors['Y'].push_back(1.0);
    colors['Y'].push_back(1.0);
    colors['Y'].push_back(0.0);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);

    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("RubixCube");

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    setup();

    glutMainLoop();
}
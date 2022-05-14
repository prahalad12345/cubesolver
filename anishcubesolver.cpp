///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a square.
// 
// Sumanta Guha.
///////////////////////////////////
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <cstdio>
#include <algorithm>
//bahkrigandchod
using namespace std;

vector< vector < char > > cube;
map < char, vector< float > > colors;
vector < vector <int> > offset;
string res,moves;
int movee=0;
// Drawing routine.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate scene.
static float Xvalue = 0.0, Zvalue = -5.0; // Co-ordinates of the sphere.

void make_cuboid(float l, float b, float h)
{
    glScalef(l, h, b);
    glutSolidCube(1);
    glScalef(1/l, 1/h, 1/b);
}

void createFaces() {
    // start with UP
    for(int i=0; i<9; i++) {
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslated(offset[i][0], 15, offset[i][1]);
        glScalef(1, 0.1, 1);
        glColor3f(colors[cube[0][i]][0], colors[cube[0][i]][1], colors[cube[0][i]][2]);
        glutSolidCube(8);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    // RIGHT
    for(int i=0; i<9; i++) {
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslated(15, offset[i][1], offset[i][0]);
        glScalef(0.1, 1, 1);
        glColor3f(colors[cube[1][i]][0], colors[cube[1][i]][1], colors[cube[1][i]][2]);
        glutSolidCube(8);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    // FRONT
    for(int i=0; i<9; i++) {
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslated(offset[i][0], offset[i][1], -15);
        glScalef(1, 1, 0.1);
        glColor3f(colors[cube[2][i]][0], colors[cube[2][i]][1], colors[cube[2][i]][2]);
        glutSolidCube(8);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    // DOWN
    for(int i=0; i<9; i++) {
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslated(offset[i][0], -15, -offset[i][1]);
        glScalef(1, 0.1, 1);
        glColor3f(colors[cube[3][i]][0], colors[cube[3][i]][1], colors[cube[3][i]][2]);
        glutSolidCube(8);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    // LEFT
    for(int i=0; i<9; i++) {
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslated(-15, offset[i][1], -offset[i][0]);
        glScalef(0.1, 1, 1);
        glColor3f(colors[cube[4][i]][0], colors[cube[4][i]][1], colors[cube[4][i]][2]);
        glutSolidCube(8);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    // BACK
    for(int i=0; i<9; i++) {
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslated(-offset[i][0], offset[i][1], 15);
        glScalef(1, 1, 0.1);
        glColor3f(colors[cube[5][i]][0], colors[cube[5][i]][1], colors[cube[5][i]][2]);
        glutSolidCube(8);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();

    }
}
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(Xangle, 1.0, 0.0, 0.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glDepthFunc(GL_LESS);
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidCube(29.9);
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();
    createFaces();
    glFlush();
}

// Initialization routine.
void setup(void)
{
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glEnable(GL_DEPTH_TEST);
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

void solver(){
 FILE *fp;
 /*cube = {
    {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},  // UP
    {'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},  // RIGHT
    {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},  // FRONT
    {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},  // DOWN
    {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'},  // LEFT
    {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'} // Back
    };
    */
 string removefile="rm input.txt";
 int sys1=system(removefile.c_str());
 string addfile="touch input.txt";
 int sys2=system(addfile.c_str());
 string s="";
 int i;
 for(int k=0;k<6;k++){
 if(k == 1)
 i = 4;
 else if(k == 4)
 i = 1;
 else
 i = k;
 for(int j=0;j<9;j++){
 cout<<cube[i][j]<<" ";
 if(cube[i][j]=='R')
 s+="U";
 else if(cube[i][j]=='G')
 s+="L";
 else if(cube[i][j]=='W')
 s+="F";
 else if(cube[i][j]=='O')
 s+="D";
 else if(cube[i][j]=='B')
 s+="R";
 else
 s+="B";
 }
 cout<<endl;
 }
 cout<<endl;
 
 swap(s[0],s[2]);
 swap(s[3],s[5]);
 swap(s[6],s[8]);
 
 swap(s[18],s[20]);
 swap(s[21],s[23]);
 swap(s[24],s[26]);

 swap(s[9], s[11]);
 swap(s[12], s[14]);
 swap(s[15], s[17]);
 
 swap(s[36],s[38]);
 swap(s[39],s[41]);
 swap(s[42],s[44]);
 
 swap(s[27],s[29]);
 swap(s[30],s[32]);
 swap(s[33],s[35]);

 swap(s[45],s[47]);
 swap(s[48],s[50]);
 swap(s[51],s[53]);
 /*
 
 
 

 

 

 for(int i=9;i<18;i++)
 swap(s[i],s[i+27]);


*/
 for(int i=0;i<54;i++){
 cout<<s[i]<<" ";
 if(i%9==8)
 cout<<endl;
 }
 
 fp=fopen("input.txt","w+");
 fprintf(fp,"%s",s.c_str());
 fclose(fp);
 string compile="python3 solver.py";
 int sys3=system(compile.c_str());
 FILE *fp2;
 fp2=fopen("output.txt","r");
 char res[50000];
 fscanf(fp2,"%s",res);
 moves=res;
}

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
 // u is clockwise
 case 'u':
 // Left face clockwise
 if(movee==0){
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
 else if(movee==1){
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
 //Back to Up
 copycube[5][6]=cube[0][2];
 copycube[5][3]=cube[0][5];
 copycube[5][0]=cube[0][8];
 //Up to Front
 copycube[0][2]=cube[2][2];
 copycube[0][5]=cube[2][5];
 copycube[0][8]=cube[2][8];
 //Front to down
 copycube[2][2]=cube[3][2];
 copycube[2][5]=cube[3][5];
 copycube[2][8]=cube[3][8];
 //Down to Back
 copycube[3][8]=cube[5][0];
 copycube[3][5]=cube[5][3];
 copycube[3][2]=cube[5][6]; 
 }
 else if(movee==2){
 /*Face Transformation*/
 copycube[0][6] = cube[0][8]; 
 copycube[0][3] = cube[0][7];
 copycube[0][0] = cube[0][6];
 copycube[0][7] = cube[0][5];
 copycube[0][1] = cube[0][3];
 copycube[0][8] = cube[0][2];
 copycube[0][5] = cube[0][1];
 copycube[0][2] = cube[0][0];
 //end Face
 copycube[4][0]=cube[2][0];
 copycube[4][1]=cube[2][1];
 copycube[4][2]=cube[2][2];

 copycube[2][0]=cube[1][0];
 copycube[2][1]=cube[1][1];
 copycube[2][2]=cube[1][2];
 
 copycube[1][0]=cube[5][0];
 copycube[1][1]=cube[5][1];
 copycube[1][2]=cube[5][2];
 
 copycube[5][0]=cube[4][0];
 copycube[5][1]=cube[4][1];
 copycube[5][2]=cube[4][2];
 }
 else if(movee==3){
 /*Face Transformation*/
 copycube[3][6] = cube[3][8]; 
 copycube[3][3] = cube[3][7];
 copycube[3][0] = cube[3][6];
 copycube[3][7] = cube[3][5];
 copycube[3][1] = cube[3][3];
 copycube[3][8] = cube[3][2];
 copycube[3][5] = cube[3][1];
 copycube[3][2] = cube[3][0];
 //end Face

 copycube[2][6]=cube[4][6];
 copycube[2][7]=cube[4][7];
 copycube[2][8]=cube[4][8];
 copycube[1][6]=cube[2][6];
 copycube[1][7]=cube[2][7];
 copycube[1][8]=cube[2][8];
 copycube[5][6]=cube[1][6];
 copycube[5][7]=cube[1][7];
 copycube[5][8]=cube[1][8];
 copycube[4][6]=cube[5][6];
 copycube[4][7]=cube[5][7];
 copycube[4][8]=cube[5][8];
 }
 else if(movee==4){
 // ok
 copycube[2][0] = cube[2][6]; 
 copycube[2][1] = cube[2][3];
 copycube[2][2] = cube[2][0];
 copycube[2][3] = cube[2][7];
 copycube[2][5] = cube[2][1];
 copycube[2][6] = cube[2][8];
 copycube[2][7] = cube[2][5];
 copycube[2][8] = cube[2][2];

 copycube[3][2]=cube[1][0];
 copycube[3][1]=cube[1][3];
 copycube[3][0]=cube[1][6];

 copycube[1][6]=cube[0][8];
 copycube[1][3]=cube[0][7];
 copycube[1][0]=cube[0][6];

 copycube[4][2]=cube[3][0];
 copycube[4][5]=cube[3][1];
 copycube[4][8]=cube[3][2];

 copycube[0][8]=cube[4][2];
 copycube[0][7]=cube[4][5];
 copycube[0][6]=cube[4][8];
 }
 else if(movee==5){
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
 cube=copycube;
 for(int i=0;i<6;i++){
 for(int j=0;j<9;j++){
 cout<<cube[i][j]<<" ";
 }
 cout<<endl;
 cout<<endl;
 }
 glutPostRedisplay();
 break;
 case 'o':
 // Left face clockwise
 if(movee==0){
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
 else if(movee==1){
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
 //Back to Up
 copycube[0][2]=cube[5][6];
 copycube[0][5]=cube[5][3];
 copycube[0][8]=cube[5][0];
 //Up to Front
 copycube[2][2]=cube[0][2];
 copycube[2][5]=cube[0][5];
 copycube[2][8]=cube[0][8];
 //Front to down
 copycube[3][2]=cube[2][2];
 copycube[3][5]=cube[2][5];
 copycube[3][8]=cube[2][8];
 //Down to Back
 copycube[5][0]=cube[3][8];
 copycube[5][3]=cube[3][5];
 copycube[5][6]=cube[3][2]; 
 }
 else if(movee==2){
 /*Face Transformation*/
 copycube[0][6] = cube[0][0]; 
 copycube[0][3] = cube[0][1];
 copycube[0][0] = cube[0][2];
 copycube[0][7] = cube[0][3];
 copycube[0][1] = cube[0][5];
 copycube[0][8] = cube[0][6];
 copycube[0][5] = cube[0][7];
 copycube[0][2] = cube[0][8];
 //end Face
 copycube[2][0]=cube[4][0];
 copycube[2][1]=cube[4][1];
 copycube[2][2]=cube[4][2];

 copycube[1][0]=cube[2][0];
 copycube[1][1]=cube[2][1];
 copycube[1][2]=cube[2][2];
 
 copycube[5][0]=cube[1][0];
 copycube[5][1]=cube[1][1];
 copycube[5][2]=cube[1][2];
 
 copycube[4][0]=cube[5][0];
 copycube[4][1]=cube[5][1];
 copycube[4][2]=cube[5][2];
 }
 else if(movee==3){
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
 //end Face

 copycube[4][6]=cube[2][6];
 copycube[4][7]=cube[2][7];
 copycube[4][8]=cube[2][8];

 copycube[2][6]=cube[1][6];
 copycube[2][7]=cube[1][7];
 copycube[2][8]=cube[1][8];
 
 copycube[1][6]=cube[5][6];
 copycube[1][7]=cube[5][7];
 copycube[1][8]=cube[5][8];
 
 copycube[5][6]=cube[4][6];
 copycube[5][7]=cube[4][7];
 copycube[5][8]=cube[4][8];
 }
 else if(movee==4){
 // ok
 copycube[2][0] = cube[2][2]; 
 copycube[2][1] = cube[2][5];
 copycube[2][2] = cube[2][8];
 copycube[2][3] = cube[2][1];
 copycube[2][5] = cube[2][7];
 copycube[2][6] = cube[2][0];
 copycube[2][7] = cube[2][3];
 copycube[2][8] = cube[2][6];

 copycube[1][0]=cube[3][2];
 copycube[1][3]=cube[3][1];
 copycube[1][6]=cube[3][0];

 copycube[0][8]=cube[1][6];
 copycube[0][7]=cube[1][3];
 copycube[0][6]=cube[1][0];

 copycube[3][0]=cube[4][2];
 copycube[3][1]=cube[4][5];
 copycube[3][2]=cube[4][8];

 copycube[4][2]=cube[0][8];
 copycube[4][5]=cube[0][7];
 copycube[4][8]=cube[0][6];
 }
 else if(movee==5){
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
 cube=copycube;
 for(int i=0;i<6;i++){
 for(int j=0;j<9;j++){
 cout<<cube[i][j]<<" ";
 }
 cout<<endl;
 cout<<endl;
 }
 glutPostRedisplay();
 break;
 case 'g':
 solver();
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
    cube.resize(6);
    char arr[6]={'R','G','W','O','B','Y'};
    for(int i=0;i<6;i++){
        for(int j=0;j<9;j++){
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
    {'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},  // UP
    {'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G'},  // RIGHT
    {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},  // FRONT
    {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},  // DOWN
    {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'},  // LEFT
    {'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'} // Back
    };
    */
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
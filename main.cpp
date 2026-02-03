#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <GL/glut.h>

using namespace std;

GLenum mode = GL_POLYGON;

//Transformation Variables
float tDistanceX = 0.0;
float tDistanceY = 0.0;
bool mousePressed = false;
bool reset = true;
float brickX = 0.0;
float brickY = 0.0;
float mouseX1 = 0.0;
float mouseY1 = 0.0;
float mouseX2 = 0.0;
float mouseY2 = 0.0;
float velX = 0.0;
float velY = 0.0;
float stepSize = 0.2;
float grav = 0.1;
float rotX = 30.0;
float rotY = -30.0;
float rotZ = 0.0;
bool simulate = false;


void init()
{
   glClearColor(0.258, 0.596, 0.569, 1.0);
   glEnable(GL_DEPTH_TEST);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-200.0, 200.0, -100.0, 100.0, -100.0, 100.0);
}

void makeCube(float midx, float midy, float midz, float size)
{
   // Define 8 vertices
   float ax = midx - size / 2;
   float ay = midy - size / 2;
   float az = midz + size / 2;
   float bx = midx + size / 2;
   float by = midy - size / 2;
   float bz = midz + size / 2;
   float cx = midx + size / 2;
   float cy = midy + size / 2;
   float cz = midz + size / 2;
   float dx = midx - size / 2;
   float dy = midy + size / 2;
   float dz = midz + size / 2;
   float ex = midx - size / 2;
   float ey = midy - size / 2;
   float ez = midz - size / 2;
   float fx = midx + size / 2;
   float fy = midy - size / 2;
   float fz = midz - size / 2;
   float gx = midx + size / 2;
   float gy = midy + size / 2;
   float gz = midz - size / 2;
   float hx = midx - size / 2;
   float hy = midy + size / 2;
   float hz = midz - size / 2;

   // Draw 6 faces
   glBegin(mode);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(bx, by, bz);
   glVertex3f(cx, cy, cz);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(mode);
   glColor3f(0.8, 0.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(dx, dy, dz);
   glVertex3f(hx, hy, hz);
   glVertex3f(ex, ey, ez);
   glEnd();

   glBegin(mode);
   glColor3f(0.4, 0.0, 0.0);
   glVertex3f(ax, ay, az);
   glVertex3f(ex, ey, ez);
   glVertex3f(fx, fy, fz);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(mode);
   glColor3f(0.6, 0.0, 0.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(fx, fy, fz);
   glVertex3f(ex, ey, ez);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(mode);
   glColor3f(0.5, 0.0, 0.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(cx, cy, cz);
   glVertex3f(bx, by, bz);
   glVertex3f(fx, fy, fz);
   glEnd();

   glBegin(mode);
   glColor3f(0.7, 0.0, 0.0);
   glVertex3f(gx, gy, gz);
   glVertex3f(hx, hy, hz);
   glVertex3f(dx, dy, dz);
   glVertex3f(cx, cy, cz);
   glEnd();
}

// Mouse Listner
void mouse(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
      simulate = false;
      velX = 0.0;
      velY = 0.0;
      rotX = 30.0;
      rotY = -30.0;
      rotZ = 0.0;
      grav = 0.1;
      mouseX1 = ((((float)x / 1000) - 0.5) * 400);
      mouseY1 = -((((float)y / 500) - 0.5) * 200);
      mouseX2 = mouseX1;
      mouseY2 = mouseY1;
      brickX = mouseX1;
      brickY = mouseY1;
      mousePressed = true;
      reset = false;
      glutPostRedisplay();
   }

   else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
   {
      cout << "STUFF" << endl;
      velX = mouseX1 - mouseX2;
      velY = mouseY1 - mouseY2;
      cout << "velX is " << velX << endl;
      cout << "velY is " << velY << endl;
      mousePressed = false;
      simulate = true;
   }
}

// Mouse Motion Listener
void motion(int x, int y)
{
   if (mousePressed)
   {
      mouseX2 = ((((float)x / 1000) - 0.5) * 400);
      mouseY2 = -((((float)y / 500) - 0.5) * 200);
      brickX = mouseX2;
      brickY = mouseY2;
      glutPostRedisplay();
   }
}

// Timer for Transformation
void timer(int time)
{
   if (simulate)
   {
      velY -= grav;
      if (grav >= 1.8)  // Ensures gravity doesn't get too strong
         grav = grav;
      else
         grav *= 1.1;
      brickX += velX * stepSize;
      brickY += velY * stepSize;

      if (brickX >= 200.0 || brickX <= -200.0)  // Bouncing conditions
      {
         velX = -velX;
      }
      if (brickY <= -100.0)   // Reset if hit ground
      {
         reset = true;
         simulate = false;
         velX = 0.0;
         velY = 0.0;
         grav = 0.1;
         mouseX1 = 0.0;
         mouseX2 = 0.0;
         mouseY1 = 0.0;
         mouseY2 = 0.0;
      }
      rotX += 5.0;
      rotY -+ 5.0;
      rotZ += 5.0;

      glutPostRedisplay();
   }

   glutTimerFunc(33, timer, 0);
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   if (reset)
   {
      glTranslatef(-150.0, -50.0, 0.0);
      rotX = 30.0;
      rotY = -30.0;
      rotZ = 0.0;
   }
   else
   {
      glTranslatef(brickX, brickY, 0.0);
   }
   glRotatef(rotX, 1.0, 0.0, 0.0);
   glRotatef(rotY, 0.0, 1.0, 0.0);
   glRotatef(rotZ, 0.0, 0.0, 1.0);
   makeCube(0.0, 0.0, 0.0, 10.0);

   glFlush();
}

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(1000, 500);
   glutInitWindowPosition(500, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Block Slinger");
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   glutTimerFunc(33, timer, 0);
   glutDisplayFunc(display);
   init();
   glutMainLoop();
   return 0;
}
#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

float triangle[3][2] = {{0, 50}, {-50, -50}, {50, -50}};
float angle = 45.0;

void drawTriangle(float pts[3][2]) {
    glBegin(GL_TRIANGLES);
    for(int i=0;i<3;i++)
        glVertex2f(pts[i][0], pts[i][1]);
    glEnd();
}

void rotateOrigin(float pts[3][2], float theta) {
    float rad = theta * M_PI / 180.0;
    for(int i=0;i<3;i++) {
        float x = pts[i][0];
        float y = pts[i][1];
        pts[i][0] = x*cos(rad) - y*sin(rad);
        pts[i][1] = x*sin(rad) + y*cos(rad);
    }
}

void rotateFixed(float pts[3][2], float theta, float h, float k) {
    float rad = theta * M_PI / 180.0;
    for(int i=0;i<3;i++) {
        float x = pts[i][0] - h;
        float y = pts[i][1] - k;

        float xr = x*cos(rad) - y*sin(rad);
        float yr = x*sin(rad) + y*cos(rad);

        pts[i][0] = xr + h;
        pts[i][1] = yr + k;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float tri1[3][2];
    memcpy(tri1, triangle, sizeof(triangle));
    glColor3f(1,0,0);
    drawTriangle(tri1);

    rotateOrigin(tri1, angle);
    glColor3f(0,1,0);
    drawTriangle(tri1);

    float tri2[3][2];
    memcpy(tri2, triangle, sizeof(triangle));
    rotateFixed(tri2,angle,0,150);
    glColor3f(0,0,1);
    drawTriangle(tri2);

    glFlush();
}

void init() {
    glClearColor(1,1,1,1);
    gluOrtho2D(-200,200,-200,200);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutCreateWindow("Triangle Rotation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
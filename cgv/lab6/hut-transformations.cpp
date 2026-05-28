#include <GL/glut.h>
#include <cmath>
#include <cstring>
float hut[7][2] = {
    {-50,-50}, {50,-50}, {50,0}, {-50,0},   
    {-60,0}, {0,60}, {60,0}                 
};

void drawHut(float pts[7][2]) {
    glBegin(GL_QUADS);
    for(int i=0;i<4;i++)
        glVertex2f(pts[i][0], pts[i][1]);
    glEnd();

    glBegin(GL_TRIANGLES);
    for(int i=4;i<7;i++)
        glVertex2f(pts[i][0], pts[i][1]);
    glEnd();
}

void translate(float pts[7][2], float tx, float ty){
    for(int i=0;i<7;i++){
        pts[i][0]+=tx;
        pts[i][1]+=ty;
    }
}

void scaleFixed(float pts[7][2], float sx, float sy, float h, float k){
    for(int i=0;i<7;i++){
        pts[i][0] = h + sx*(pts[i][0]-h);
        pts[i][1] = k + sy*(pts[i][1]-k);
    }
}

void rotateFixed(float pts[7][2], float theta, float h, float k){
    float rad = theta*M_PI/180.0;
    for(int i=0;i<7;i++){
        float x = pts[i][0]-h;
        float y = pts[i][1]-k;

        float xr = x*cos(rad) - y*sin(rad);
        float yr = x*sin(rad) + y*cos(rad);

        pts[i][0] = xr + h;
        pts[i][1] = yr + k;
    }
}

void reflectY(float pts[7][2]){
    for(int i=0;i<7;i++)
        pts[i][0] = -pts[i][0];
}

void shear(float pts[7][2], float shx, float shy){
    for(int i=0;i<7;i++){
        float x = pts[i][0];
        float y = pts[i][1];
        pts[i][0] = x + shx*y;
        pts[i][1] = y + shy*x;
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    float h1[7][2];
    memcpy(h1, hut, sizeof(hut));
    

    scaleFixed(h1,2,2,0,0);
    glColor3f(0,1,0);
    drawHut(h1);

    scaleFixed(h1,0.5,0.5,0,0);
    glColor3f(1,0,0);
    drawHut(h1);
    
    scaleFixed(h1,0.5,0.5,0,0);
    glColor3f(0,0,1);
    drawHut(h1);

    scaleFixed(h1,2,2,0,0);
    // glColor3f(0,1,0);
    // drawHut(h1);

    translate(h1,200,0);
    glColor3f(1,0,0);
    drawHut(h1);

    reflectY(h1);
    glColor3f(1,0,0);
    drawHut(h1);

    reflectY(h1);
    //translate(h1,-200,0);
    rotateFixed(h1,45,0,0);
    glColor3f(1,0,0);
    drawHut(h1);

    

    shear(h1,0.5,0.2);
   // reflectY(h1);
    glColor3f(1,0,0);
    drawHut(h1);

   // glColor3f(0,0,1);
   // drawHut(h1);

    glFlush();
}

void init(){
    glClearColor(1,1,1,1);
    gluOrtho2D(-300,300,-300,300);
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitWindowSize(700,700);
    glutCreateWindow("Hut Transformations");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
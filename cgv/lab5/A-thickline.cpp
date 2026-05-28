#include <GL/glut.h>
#include <cmath>
float I0 = 1.0f;
float sigma = 1.0f;

float thickLine(float h){
    float Bmin=0, Bmax=2;
    if(h>=Bmin && h<=Bmax)
        return I0;
    return 0;
}


float distanceFromLine(float x, float y,
                       float x1, float y1,
                       float x2, float y2) {
    float A = y2 - y1;
    float B = x1 - x2;
    float C = x2*y1 - x1*y2;
    return fabs(A*x + B*y + C) / sqrt(A*A + B*B);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float x1=100,y1=100,x2=500,y2=300;   
    glBegin(GL_POINTS);
    for(int x=0;x<600;x++){
        for(int y=0;y<600;y++){
            float h = distanceFromLine(x+0.5,y+0.5,x1,y1,x2,y2);
            float intensity = thickLine(h);
            glColor3f(intensity,intensity,intensity);
            glVertex2i(x,y);
        }
    }
    glEnd();

    glFlush();
}

void init(){
    glClearColor(0,0,0,1);
    gluOrtho2D(0,600,0,600);
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitWindowSize(600,600);
    glutCreateWindow("Gaussian Antialiasing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

const double xmin = 250, ymin = 250, xmax = 750, ymax = 750;

void clipLeft(double x1, double y1, double x2, double y2, double *nx, double *ny) {
    *ny = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
    *nx = xmin;
}
void clipRight(double x1, double y1, double x2, double y2, double *nx, double *ny) {
    *ny = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
    *nx = xmax;
}
void clipBottom(double x1, double y1, double x2, double y2, double *nx, double *ny) {
    *nx = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
    *ny = ymin;
}
void clipTop(double x1, double y1, double x2, double y2, double *nx, double *ny) {
    *nx = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
    *ny = ymax;
}

void nlnClip(double x1, double y1, double x2, double y2) {
    double nx1 = x1, ny1 = y1, nx2 = x2, ny2 = y2;

    
    if (x1 >= xmin && x1 <= xmax && y1 >= ymin && y1 <= ymax) {
        if (x2 >= xmin && x2 <= xmax && y2 >= ymin && y2 <= ymax) {
            glVertex2d(x1, y1); glVertex2d(x2, y2);
            return;
        }
        if (x2 > xmax) {
            double mTop = (ymax - y1) / (xmax - x1);
            double mBot = (ymin - y1) / (xmax - x1);
            double mLine = (y2 - y1) / (x2 - x1);
            if (mLine > mTop) clipTop(x1, y1, x2, y2, &nx2, &ny2);
            else if (mLine < mBot) clipBottom(x1, y1, x2, y2, &nx2, &ny2);
            else clipRight(x1, y1, x2, y2, &nx2, &ny2);
        } else if (x2 < xmin) { 
            double mTop = (ymax - y1) / (xmin - x1);
            double mBot = (ymin - y1) / (xmin - x1);
            double mLine = (y2 - y1) / (x2 - x1);
            if (mLine < mTop) clipTop(x1, y1, x2, y2, &nx2, &ny2);
            else if (mLine > mBot) clipBottom(x1, y1, x2, y2, &nx2, &ny2);
            else clipLeft(x1, y1, x2, y2, &nx2, &ny2);
        } else if (y2 > ymax) clipTop(x1, y1, x2, y2, &nx2, &ny2);
        else clipBottom(x1, y1, x2, y2, &nx2, &ny2);

        glVertex2d(x1, y1); glVertex2d(nx2, ny2);
    } 
    
    else if (x1 < xmin && y1 >= ymin && y1 <= ymax) {
        if (x2 < xmin) return; 
        
        double mTop = (ymax - y1) / (xmin - x1);
        double mBot = (ymin - y1) / (xmin - x1);
        double mLine = (y2 - y1) / (x2 - x1);

        if (mLine > mTop || mLine < mBot) return; 

        clipLeft(x1, y1, x2, y2, &nx1, &ny1);

        if (x2 > xmax) {
            double mTR = (ymax - y1) / (xmax - x1);
            double mBR = (ymin - y1) / (xmax - x1);
            if (mLine > mTR) clipTop(x1, y1, x2, y2, &nx2, &ny2);
            else if (mLine < mBR) clipBottom(x1, y1, x2, y2, &nx2, &ny2);
            else clipRight(x1, y1, x2, y2, &nx2, &ny2);
        } else {
            if (y2 > ymax) clipTop(x1, y1, x2, y2, &nx2, &ny2);
            else if (y2 < ymin) clipBottom(x1, y1, x2, y2, &nx2, &ny2);
            else { nx2 = x2; ny2 = y2; } 
        }
        glVertex2d(nx1, ny1); glVertex2d(nx2, ny2);
    }

    else if (x1 < xmin && y1 > ymax) {
        double mTR = (ymax - y1) / (xmax - x1);
        double mBL = (ymin - y1) / (xmin - x1);
        double mLine = (y2 - y1) / (x2 - x1);

        if (mLine < mTR || mLine > mBL) return; 

        double mCorner = (ymax - y1) / (xmin - x1);
        if (mLine < mCorner) clipTop(x1, y1, x2, y2, &nx1, &ny1);
        else clipLeft(x1, y1, x2, y2, &nx1, &ny1);

        if (x2 > xmax) {
            double mBR = (ymin - y1) / (xmax - x1);
            if (mLine < mBR) clipBottom(x1, y1, x2, y2, &nx2, &ny2);
            else clipRight(x1, y1, x2, y2, &nx2, &ny2);
        } else if (y2 < ymin) {
            clipBottom(x1, y1, x2, y2, &nx2, &ny2);
        } else {
            nx2 = x2; ny2 = y2; 
        }
        glVertex2d(nx1, ny1); glVertex2d(nx2, ny2);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(xmin, ymin); glVertex2i(xmax, ymin);
        glVertex2i(xmax, ymax); glVertex2i(xmin, ymax);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    for (int i = 0; i < 40; i++) {
        nlnClip(rand() % 1000, rand() % 1000, rand() % 1000, rand() % 1000);
    }
    glEnd();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, 1000, 0, 1000);
}

int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Pure NLN Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
#include <GL/glut.h>  
#include <cmath>      
#include <algorithm>  
#include <iostream>


using namespace std;


const int WINDOW_WIDTH = 680;
const int WINDOW_HEIGHT = 680;


void drawLineBresenham(int x1, int y1, int x2, int y2) {
    
    y1=WINDOW_HEIGHT-y1;
    y2=WINDOW_HEIGHT-y2;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    
    bool isSteep = dy > dx;
    
    if (isSteep) {
        swap(dx, dy);
    }

    int p = 2 * dy - dx;
    int x = x1;
    int y = y1;
    

    glBegin(GL_POINTS); 
    
    for (int i = 0; i <= dx; i++) {
        
        glVertex2i(x, y);
        
        if (p >= 0) {
            if (isSteep) x += sx;
            else y += sy;
            p -= 2 * dx;
        }
        
        if (isSteep) y += sy;
        else x += sx;
        
        p += 2 * dy;
    }
    
    glEnd();
}

void display() {
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    glColor3f(1.0, 1.0, 1.0);
    
 
    drawLineBresenham(19, 430, 225, 595);
    drawLineBresenham(19, 430, 19, 240);
    drawLineBresenham(225,318, 225, 595);
    drawLineBresenham(11,250, 105, 127);
    drawLineBresenham(105,127, 235, 335);
    drawLineBresenham(225,595, 565, 490);
    drawLineBresenham(565,490, 563, 340);
    drawLineBresenham(563,340, 630, 330);
    drawLineBresenham(630,476, 630, 330);
    drawLineBresenham(630,476, 620, 468);
    drawLineBresenham(564,485, 620, 468);
    drawLineBresenham(620,468, 622, 332);
    drawLineBresenham(107,113, 4, 242);
    drawLineBresenham(4,242, 11, 250);
    drawLineBresenham(238,320, 107, 113);
    drawLineBresenham(238,320, 674, 250);
    drawLineBresenham(235,335, 670, 259);
    drawLineBresenham(674,250, 670, 259);
    drawLineBresenham(107,113, 570, 84);
    drawLineBresenham(570,84, 674, 250);
    drawLineBresenham(655,260, 658, 468);
    drawLineBresenham(630,476, 658, 468);
    drawLineBresenham(65,385, 66, 285);
    drawLineBresenham(65,385, 154, 434);
    drawLineBresenham(154,434, 153, 322);
    drawLineBresenham(153,322, 66, 285);
    drawLineBresenham(71,296, 143, 327);
    drawLineBresenham(143,327, 143, 418);
    drawLineBresenham(143,418, 71, 378);
    drawLineBresenham(103,309, 103, 349);
    drawLineBresenham(103,349, 71, 333);
    drawLineBresenham(108,311, 108, 351);
    drawLineBresenham(108,351, 143, 369);
    drawLineBresenham(71,339, 103, 355);
    drawLineBresenham(103,355, 103, 395);
    drawLineBresenham(108,358, 143, 376);
    drawLineBresenham(108,358, 108, 398);
    drawLineBresenham(71,296, 71, 378);
    drawLineBresenham(286,373, 286, 478);
    drawLineBresenham(286,478, 346, 466);
    drawLineBresenham(346,466, 346, 362);
    drawLineBresenham(346,362, 286, 373);
    drawLineBresenham(294,379, 294, 469);
    drawLineBresenham(294,469, 338, 461);
    drawLineBresenham(338,461, 338, 371);
    drawLineBresenham(338,371, 294, 379);

    
    
    glFlush();
}

void init() {
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    
   
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Algorithm - GLUT"); 
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
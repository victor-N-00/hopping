#include <GL/glut.h>
#include <math.h>

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;

    while (x <= y) {
        plot(xc + x, yc + y);
        plot(xc - x, yc + y);
        plot(xc + x, yc - y);
        plot(xc - x, yc - y);
        plot(xc + y, yc + x);
        plot(xc - y, yc + x);
        plot(xc + y, yc - x);
        plot(xc - y, yc - x);

        if (p < 0)
            p += 2*x + 3;
        else {
            p += 2*(x - y) + 5;
            y--;
        }
        x++;
    }
}

void drawEllipse(int xc, int yc, int a, int b) {
    int x = 0, y = b;
    float p1 = b*b - a*a*b + 0.25*a*a;

    while (2*b*b*x < 2*a*a*y) {
        plot(xc + x, yc + y);
        plot(xc - x, yc + y);
        plot(xc + x, yc - y);
        plot(xc - x, yc - y);

        if (p1 < 0) {
            x++;
            p1 += 2*b*b*x + b*b;
        } else {
            x++;
            y--;
            p1 += 2*b*b*x - 2*a*a*y + b*b;
        }
    }

    float p2 = b*b*(x+0.5)*(x+0.5) + a*a*(y-1)*(y-1) - a*a*b*b;

    while (y > 0) {
        plot(xc + x, yc + y);
        plot(xc - x, yc + y);
        plot(xc + x, yc - y);
        plot(xc - x, yc - y);

        if (p2 > 0) {
            y--;
            p2 += a*a - 2*a*a*y;
        } else {
            x++;
            y--;
            p2 += 2*b*b*x - 2*a*a*y + a*a;
        }
    }
}

void drawHalfEllipse(int xc, int yc, int a, int b) {
    int x = 0;
    int y = b;
    float p1 = b*b - a*a*b + 0.25*a*a;

    // Region 1
    while (2*b*b*x < 2*a*a*y) {
        plot(xc + x, yc - y);
        plot(xc - x, yc - y);

        if (p1 < 0) {
            x++;
            p1 += 2*b*b*x + b*b;
        } else {
            x++;
            y--;
            p1 += 2*b*b*x - 2*a*a*y + b*b;
        }
    }

    // Region 2
    float p2 = b*b*(x+0.5)*(x+0.5)
             + a*a*(y-1)*(y-1)
             - a*a*b*b;

    while (y > 0) {
        plot(xc + x, yc - y);
        plot(xc - x, yc - y);

        if (p2 > 0) {
            y--;
            p2 += a*a - 2*a*a*y;
        } else {
            x++;
            y--;
            p2 += 2*b*b*x - 2*a*a*y + a*a;
        }
    }
}


void drawLine(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawEllipse(0, 120, 60, 80);

    drawCircle(-20, 140, 10);
    drawCircle( 20, 140, 10);

    drawLine(0, 125, -10, 105);
    drawLine(-10, 105, 10, 105);
    drawLine(10, 105, 0, 125);

    drawLine(-30, 90, 30, 90);
    drawHalfEllipse(0, 90, 30, 15);

    drawLine(0, 40, 0, -60);

    drawLine(-40, 40, 40, 40);

    drawLine(0, -60, -40, -120);
    drawLine(0, -60, 40, -120);

    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 1);
    glColor3f(1, 1, 1);
    gluOrtho2D(-200, 200, -200, 200);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Stick Figure – No Inbuilt API");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}

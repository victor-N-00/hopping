#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>

float chairAngle = 0.0f;
float tableOffsetX = 0.0f;
float chairOffsetX = 0.0f;
bool isCollided = false;
int collisionTime = 0;
bool animationDone = false;

void rotatePoint(float cx, float cy, float x, float y, float angle, float *rx, float *ry) {
    float rad = angle * 3.14159f / 180.0f;
    float s = sin(rad);
    float c = cos(rad);
    
    x -= cx;
    y -= cy;
    
    *rx = x * c - y * s + cx;
    *ry = x * s + y * c + cy;
}

bool checkCollision(float angle) {
    
    for (float y = 100; y <= 280; y += 10) {
        float rx, ry;
        rotatePoint(580, 100, 580, y, angle, &rx, &ry);
        
        if (rx >= 150 && rx <= 450 && ry >= 300 && ry <= 330) return true;
        if (rx >= 400 && rx <= 430 && ry >= 100 && ry <= 300) return true;
        if (rx >= 250 && rx <= 350 && ry >= 330 && ry <= 380) return true;
    }
    
    for (float y = 280; y <= 500; y += 10) {
        float rx, ry;
        rotatePoint(580, 100, 670, y, angle, &rx, &ry);
        
        if (rx >= 150 && rx <= 450 && ry >= 300 && ry <= 330) return true;
        if (rx >= 400 && rx <= 430 && ry >= 100 && ry <= 300) return true;
        if (rx >= 250 && rx <= 350 && ry >= 330 && ry <= 380) return true;
    }
    
    return false;
}

void drawRect(float x, float y, float w, float h, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void drawCircle(float cx, float cy, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 10) {
        float theta = i * 3.14159f / 180.0f;
        glVertex2f(cx + radius * cos(theta), cy + radius * sin(theta));
    }
    glEnd();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 360; i += 10) {
        float theta = i * 3.14159f / 180.0f;
        glVertex2f(cx + radius * cos(theta), cy + radius * sin(theta));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(50, 90);
    glVertex2f(750, 90);
    glVertex2f(750, 100);
    glVertex2f(50, 100);
    glEnd();

    glPushMatrix();
    glTranslatef(tableOffsetX, 0.0f, 0.0f);

    drawRect(170, 100, 30, 200, 0.5f, 0.3f, 0.1f); 
    drawRect(400, 100, 30, 200, 0.5f, 0.3f, 0.1f); 
    drawRect(150, 300, 300, 30, 0.5f, 0.3f, 0.1f); 

    drawRect(250, 330, 100, 50, 0.0f, 0.8f, 0.0f);

    drawCircle(280, 400, 20, 1.0f, 0.8f, 0.0f); 
    drawCircle(320, 400, 20, 1.0f, 0.0f, 0.0f); 

    glPopMatrix();

    glPushMatrix();
    glTranslatef(chairOffsetX, 0.0f, 0.0f); 
    
    glTranslatef(580, 100, 0); 
    glRotatef(chairAngle, 0, 0, 1); 
    glTranslatef(-580, -100, 0); 

    drawRect(580, 100, 30, 150, 0.0f, 0.6f, 1.0f); // Front leg
    drawRect(670, 100, 30, 150, 0.0f, 0.6f, 1.0f); // Back leg
    drawRect(580, 250, 120, 30, 0.0f, 0.6f, 1.0f); // Seat
    drawRect(670, 280, 30, 220, 0.0f, 0.6f, 1.0f); // Backrest

    glPopMatrix();

    glutSwapBuffers();
}

void update(int value) {
    if (!animationDone) {
        if (!isCollided) {
            chairAngle += 1.5f; 
            if (checkCollision(chairAngle)) {
                isCollided = true;
                collisionTime = glutGet(GLUT_ELAPSED_TIME);
            }
        } else {
            
            int elapsed = glutGet(GLUT_ELAPSED_TIME) - collisionTime;
            if (elapsed <= 1000) {
                tableOffsetX -= 2.0f;
                chairOffsetX -= 2.0f;
            } else {
                animationDone = true;
            }
        }
    }
    
    glutPostRedisplay();
    //60 fps
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Chair and Table Collision Animation");
    
    init();
    
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);
    
    glutMainLoop();
    return 0;
}
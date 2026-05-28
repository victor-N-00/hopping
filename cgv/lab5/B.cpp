#include <GL/glut.h>
#include <cmath>

float A=1, B=-1, C=0;   

float edgeWeight(float x,float y){
    float dist = fabs(A*x + B*y + C)/sqrt(A*A+B*B);
    float Bmax=1.0;
    if(dist<=Bmax)
        return (Bmax-dist)/Bmax;
    return -1;  
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for(int x=0;x<100;x++){
        for(int y=0;y<100;y++){

            float value = A*x + B*y + C;
            float w = edgeWeight(x+0.5,y+0.5);

            if(w>=0){ 
                float r = (1-w);
                float g = 0;
                float b = w;
                glColor3f(r,g,b);
            }
            else{
                if(value>0)
                    glColor3f(0,0,1);  
                else
                    glColor3f(1,0,0);  
            }

            glVertex2i(x,y);
        }
    }
    glEnd();

    glFlush();
}

void init(){
    glClearColor(0,0,0,1);
    gluOrtho2D(0,100,0,100);
}

void reshape(int w, int h){
    glViewport(0, 0, w, h);          // Update viewport

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);          // Match projection to new window size

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitWindowSize(600,600);
    glutCreateWindow("Surface Division with Weighted Edge");
    //glutReshapeFunc(reshape);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}

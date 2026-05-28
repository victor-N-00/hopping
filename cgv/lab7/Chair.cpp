#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#ifndef M_PI
#endif
float tableX = 150.0f;
float chairX = 500.0f;
float chairTheta = 0.0f;
float omega = 0.0f;
float alpha = 150.0f;
float vx = 0.0f;
float ax = 120.0f;
int state = -1;
float waitTimer = 1.0f;
void drawRectWithBorder(float x1, float y1, float x2, float y2, float r,float g, float b) {
  glColor3f(r, g, b);
  glRectf(x1, y1, x2, y2);
  glColor3f(0.0f, 0.0f, 0.0f);
  glLineWidth(3.0f);
  glBegin(GL_LINE_LOOP);
  glVertex2f(x1, y1);
  glVertex2f(x2, y1);
  glVertex2f(x2, y2);
  glVertex2f(x1, y2);
  glEnd();
}
void drawCircleWithBorder(float cx, float cy, float rad, float r, float g,
                          float b) {
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(cx, cy);
  for (int i = 0; i <= 360; i += 10) {
    float angle = i * M_PI / 180.0f;
    glVertex2f(cx + cos(angle) * rad, cy + sin(angle) * rad);
  }
  glEnd();
  glColor3f(0.0f, 0.0f, 0.0f);
  glLineWidth(3.0f);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < 360; i += 10) {
    float angle = i * M_PI / 180.0f;
    glVertex2f(cx + cos(angle) * rad, cy + sin(angle) * rad);
  }
  glEnd();
}
void drawTableAndObjects() {
  float tr = 0.6f, tg = 0.4f, tb = 0.2f;
  drawRectWithBorder(0, 180, 240, 210, tr, tg, tb);
  drawRectWithBorder(10, 0, 40, 180, tr, tg, tb);
  drawRectWithBorder(190, 0, 220, 180, tr, tg, tb);
  drawRectWithBorder(50, 210, 190, 260, 0.0f, 1.0f, 0.0f);
  drawCircleWithBorder(100, 280, 20, 1.0f, 1.0f, 0.0f);
  drawCircleWithBorder(140, 280, 20, 1.0f, 0.0f, 0.0f);
}
void drawChair() {
  float cr = 0.0f, cg = 0.6f, cb = 1.0f;
  drawRectWithBorder(80, 0, 110, 280, cr, cg, cb);
  drawRectWithBorder(0, 0, 30, 100, cr, cg, cb);
  drawRectWithBorder(0, 100, 110, 130, cr, cg, cb);
}
int main(void) {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Chair and Table Animation", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 800, 0, 600, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  double lastTime = glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    double currentTime = glfwGetTime();
    float dt = (float)(currentTime - lastTime);
    lastTime = currentTime;
    if (dt > 0.05f)
      dt = 0.05f;
    if (state == -1) {
      waitTimer -= dt;
      if (waitTimer <= 0.0f)
        state = 0;
    } else if (state == 0) {
      omega += alpha * dt;
      chairTheta += omega * dt;
      float dx = (tableX + 240.0f) - chairX;
      float dy = 210.0f;
      float rad = -chairTheta * M_PI / 180.0f;
      float localX = dx * cos(rad) - dy * sin(rad);
      float localY = dx * sin(rad) + dy * cos(rad);
      if (localX >= 80.0f && localY >= 130.0f && localY <= 280.0f) {
        state = 1;
        vx = -omega * 2.5f;
      }
    } else if (state == 1) {
      vx += ax * dt;
      if (vx >= 0.0f) {
        vx = 0.0f;
        state = 2;
      }
      tableX += vx * dt;
      chairX += vx * dt;
    }
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(0, 0, 800, 100);
    glPushMatrix();
    glTranslatef(tableX, 100, 0);
    drawTableAndObjects();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(chairX, 100, 0);
    glRotatef(chairTheta, 0, 0, 1);
    drawChair();
    glPopMatrix();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}

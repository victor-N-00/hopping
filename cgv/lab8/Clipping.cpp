#include <GL/glut.h>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

const int x_min = 250, y_min = 250, x_max = 750, y_max = 750;
const int INSIDE = 0, LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;

struct Line {
  double x1, y1, x2, y2;
};
vector<Line> testLines;

int computeCode(double x, double y) {
  int code = INSIDE;
  if (x < x_min)
    code |= LEFT;
  else if (x > x_max)
    code |= RIGHT;
  if (y < y_min)
    code |= BOTTOM;
  else if (y > y_max)
    code |= TOP;
  return code;
}

void drawCohen(double x1, double y1, double x2, double y2) {
  int c1 = computeCode(x1, y1), c2 = computeCode(x2, y2);
  bool accept = false;
  while (true) {
    if (!(c1 | c2)) {
      accept = true;
      break;
    } else if (c1 & c2)
      break;
    else {
      int c_out = c1 ? c1 : c2;
      double x, y;
      if (c_out & TOP) {
        x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
        y = y_max;
      } else if (c_out & BOTTOM) {
        x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
        y = y_min;
      } else if (c_out & RIGHT) {
        y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
        x = x_max;
      } else if (c_out & LEFT) {
        y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
        x = x_min;
      }
      if (c_out == c1) {
        x1 = x;
        y1 = y;
        c1 = computeCode(x1, y1);
      } else {
        x2 = x;
        y2 = y;
        c2 = computeCode(x2, y2);
      }
    }
  }
  if (accept) {
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
  }
}

bool clipT(double p, double q, double &te, double &tl) {
  if (p < 0) {
    double r = q / p;
    if (r > tl)
      return false;
    if (r > te)
      te = r;
  } else if (p > 0) {
    double r = q / p;
    if (r < te)
      return false;
    if (r < tl)
      tl = r;
  } else if (q < 0)
    return false;
  return true;
}

void drawLiang(double x1, double y1, double x2, double y2) {
  double dx = x2 - x1, dy = y2 - y1, te = 0.0, tl = 1.0;
  if (clipT(-dx, x1 - x_min, te, tl) && clipT(dx, x_max - x1, te, tl) &&
      clipT(-dy, y1 - y_min, te, tl) && clipT(dy, y_max - y1, te, tl)) {
    glVertex2d(x1 + te * dx, y1 + te * dy);
    glVertex2d(x1 + tl * dx, y1 + tl * dy);
  }
}

void drawSegment(double x1, double y1, double x2, double y2) {
  glBegin(GL_LINES);
  glVertex2d(x1, y1);
  glVertex2d(x2, y2);
  glEnd();
}

void nlnClip(double x1, double y1, double x2, double y2) {
  double dx = x2 - x1;
  double dy = y2 - y1;

  if (x1 >= x_min && x1 <= x_max && y1 >= y_min && y1 <= y_max) {
    double tx = 1.0, ty = 1.0;

    if (dx > 0)
      tx = (x_max - x1) / dx;
    else if (dx < 0)
      tx = (x_min - x1) / dx;

    if (dy > 0)
      ty = (y_max - y1) / dy;
    else if (dy < 0)
      ty = (y_min - y1) / dy;

    double t = (tx < ty) ? tx : ty;
    if (t > 1.0)
      t = 1.0;

    drawSegment(x1, y1, x1 + t * dx, y1 + t * dy);
  } else if (x1 < x_min) {
    if (x2 < x_min)
      return;

    double t_left = (x_min - x1) / dx;
    double ynln = y1 + t_left * dy;

    if (ynln >= y_min && ynln <= y_max) {
      double tx = 1.0, ty = 1.0;
      if (dx > 0)
        tx = (x_max - x1) / dx;
      if (dy > 0)
        ty = (y_max - y1) / dy;
      else if (dy < 0)
        ty = (y_min - y1) / dy;

      double t_exit = (tx < ty) ? tx : ty;
      if (t_exit > 1.0)
        t_exit = 1.0;
      drawSegment(x1 + t_left * dx, y1 + t_left * dy, x1 + t_exit * dx, y1 + t_exit * dy);
    }
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1, 1, 1);
  glBegin(GL_LINE_LOOP);
  glVertex2i(x_min, y_min);
  glVertex2i(x_max, y_min);
  glVertex2i(x_max, y_max);
  glVertex2i(x_min, y_max);
  glEnd();

  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
  for (auto l : testLines)
    drawCohen(l.x1, l.y1, l.x2, l.y2);
  glEnd();

  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
  for (auto l : testLines)
    drawLiang(l.x1 + 2, l.y1 + 2, l.x2 + 2, l.y2 + 2);
  glEnd();

  glColor3f(0.0, 1.0, 1.0);
  for (auto l : testLines) {
    nlnClip(l.x1 + 4, l.y1 + 4, l.x2 + 4, l.y2 + 4);
  }

  glFlush();
}

int main(int argc, char **argv) {
  int n;
  cout << "Enter number of lines: ";
  cin >> n;

  srand(time(0));
  for (int i = 0; i < n; i++) {
    testLines.push_back({(double)(rand() % 1000), (double)(rand() % 1000),
                         (double)(rand() % 1000), (double)(rand() % 1000)});
  }

  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Clip Algorithms: Red=Cohen, Green=Liang, Cyan=NLN");
  gluOrtho2D(0, 1000, 0, 1000);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

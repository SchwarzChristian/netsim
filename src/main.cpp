#include <iostream>

#include <GL/glut.h>
#include <png.h>

#include "main.hpp"

namespace window {
  int w;
  int h;
  int zoom = 1;
}

using namespace std;

namespace key {
  const unsigned char
    zoom_in  = '+',
    zoom_out = '-',
    exit     = 27
  ;

}

void handleKeypress(unsigned char key, int x, int y) {
  switch (key) {
  case key::zoom_in:
    window::zoom++;
    if (window::zoom > 100) window::zoom = 100;
    break;
  case key::zoom_out:
    window::zoom--;
    if (window::zoom < 1) window::zoom = 1;
    break;
  case key::exit:
    exit(0);
  }
}

void handleResize(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);

  glMatrixMode (GL_MODELVIEW);
}

void handleMouse(int x, int y) {
  
}

void handleMouseButton(int button, int state, int x, int y) {
  
}

using namespace window;

void update(int counter) {
  
  glutPostRedisplay();
}

void renderScene() {
  glClear (GL_COLOR_BUFFER_BIT);

  glutSwapBuffers();
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow("CW-Clone");

  glutKeyboardFunc(handleKeypress);
  glutDisplayFunc(renderScene);
  glutReshapeFunc(handleResize);
  // glutMotionFunc(handleMouse);
  // glutMouseFunc(handleMouseButton);

  update(0);
  
  glutMainLoop();
}

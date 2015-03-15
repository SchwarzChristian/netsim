#include <iostream>

#include <GL/glut.h>
#include <png.h>

#include "main.hpp"

#define MAP_WIDTH 256
#define MAP_HEIGHT 256

#define SCROLL_AREA 10
#define SCROLL_SPEED  (32 / cam::zoom)

#define CLIP_LEFT     (window::w / 2 / cam::zoom - 1)
#define CLIP_RIGHT    (MAP_WIDTH - window::w / 2 / cam::zoom + 1)
#define CLIP_BOTTOM   (window::h / 2 / cam::zoom - MAP_HEIGHT - 1)
#define CLIP_TOP      (-window::h / 2 / cam::zoom + 1)

typedef enum {
  MOUSE_LEFT		= 0,
  MOUSE_RIGHT		= 2,
  MOUSE_WHEEL_UP	= 3,
  MOUSE_WHEEL_DOWN	= 4
} mouse_button_t;

typedef enum {
  MOUSE_STATE_DOWN	= 0,
  MOUSE_STATE_UP	= 1
} mouse_state_t;

namespace window {
  int w;
  int h;
}

namespace cam {
  int zoom = 1;
  Point pos(0, 0), key_speed(0,0), mouse_speed(0,0);
}

Chunk map;

using namespace std;

namespace key {
  const unsigned char
    zoom_in      = '+',
    zoom_out     = '-',
    scroll_left  = 'a',
    scroll_right = 'd',
    scroll_up    = 'w',
    scroll_down  = 's',
    exit         = 27
  ;

}

void handleMouse(int x, int y) {
  if (x < SCROLL_AREA) cam::mouse_speed.x = -SCROLL_SPEED;
  else if (x > window::w - SCROLL_AREA) cam::mouse_speed.x = SCROLL_SPEED;
  else cam::mouse_speed.x = 0;

  if (y < SCROLL_AREA) cam::mouse_speed.y = SCROLL_SPEED;
  else if (y > window::h - SCROLL_AREA) cam::mouse_speed.y = -SCROLL_SPEED;
  else cam::mouse_speed.y = 0;
}

void handleMouseButton(int button, int state, int x, int y) {
  if (!state) return;
  switch (button) {
  case MOUSE_WHEEL_UP: 
    cam::zoom += 1;
    if (cam::zoom > 32) cam::zoom = 32;
    break;
  case MOUSE_WHEEL_DOWN:
    cam::zoom -= 1;
    if (cam::zoom < 1) cam::zoom = 1;
    break;
  }
}

void handleKeypress(unsigned char key, int x, int y) {
  switch (key) {
  case key::zoom_in:
    cam::zoom += 1;
    if (cam::zoom > 32) cam::zoom = 32;
    break;
  case key::zoom_out:
    cam::zoom -= 1;
    if (cam::zoom < 1) cam::zoom = 1;
    break;
  case key::scroll_left:
    cam::key_speed.x = -SCROLL_SPEED;
    break;
  case key::scroll_right:
    cam::key_speed.x = SCROLL_SPEED;
    break;
  case key::scroll_up:
    cam::key_speed.y = SCROLL_SPEED;
    break;
  case key::scroll_down:
    cam::key_speed.y = -SCROLL_SPEED;
    break;
  case key::exit:
    exit(0);
  }
  glutPostRedisplay();
}

void handleKeyUp(unsigned char key, int x, int y) {
  switch (key) {
  case key::scroll_left:
  case key::scroll_right:
    cam::key_speed.x = 0;
    break;
  case key::scroll_up:
  case key::scroll_down:
    cam::key_speed.y = 0;
    break;
  }
  
}

void handleResize(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  glOrtho(-w/2, w/2, -h/2, h/2, -1.0, 1.0);

  window::w = w;
  window::h = h;

  glMatrixMode (GL_MODELVIEW);
}

using namespace window;

void update(int counter) {
  glutTimerFunc(1000 / 60.0, update, counter + 1);
  cam::pos += cam::mouse_speed + cam::key_speed;
  if (cam::pos.x < CLIP_LEFT)    cam::pos.x = CLIP_LEFT;
  if (cam::pos.x > CLIP_RIGHT)   cam::pos.x = CLIP_RIGHT;
  if (cam::pos.y < CLIP_BOTTOM)  cam::pos.y = CLIP_BOTTOM;
  if (cam::pos.y > CLIP_TOP)     cam::pos.y = CLIP_TOP;
  glutPostRedisplay();
}

void renderScene() {
  glClear(GL_COLOR_BUFFER_BIT);

  glLoadIdentity();
  
  glScalef(cam::zoom, cam::zoom, 1);
  glTranslatef(-cam::pos.x, -cam::pos.y, 0);
  map.draw();

  glLoadIdentity();

  glutSwapBuffers();
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow("netsim");

  glutKeyboardFunc(handleKeypress);
  glutKeyboardUpFunc(handleKeyUp);
  glutDisplayFunc(renderScene);
  glutReshapeFunc(handleResize);
  glutPassiveMotionFunc(handleMouse);
  glutMouseFunc(handleMouseButton);

  cam::pos.set(MAP_WIDTH / 2, -MAP_HEIGHT / 2);
  cam::zoom = 1;
  map.init(MAP_WIDTH, MAP_HEIGHT).genMountains(100, 10).genTowns(100, 10);

  update(0);
  
  glutMainLoop();
}

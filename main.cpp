////////////////////////////////////////
// tester.cpp
////////////////////////////////////////

#include "main.h"

#define WINDOWTITLE	"Cloth Simulation"

////////////////////////////////////////////////////////////////////////////////

static Tester *TESTER;
static int index = 0;
static int cap;
static bool alt = false;
static float t = -4.0f;

Cloth* clth;

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  TESTER = new Tester(argc, argv);
  clth = new Cloth(Vector3(0, 1, 0));

  glutMainLoop();
  return 0;
}

////////////////////////////////////////////////////////////////////////////////

// These are really HACKS to make glut call member functions instead of static functions
static void display()									{ TESTER->Draw(); }
static void idle()										{ TESTER->Update(); }
static void resize(int x, int y)							{ TESTER->Resize(x, y); }
static void special(int key, int x, int y) { TESTER->Special(key, x, y); }
static void keyboard(unsigned char key, int x, int y)		{ TESTER->Keyboard(key, x, y); }
static void mousebutton(int btn, int state, int x, int y)	{ TESTER->MouseButton(btn, state, x, y); }
static void mousemotion(int x, int y)					{ TESTER->MouseMotion(x, y); }

////////////////////////////////////////////////////////////////////////////////

Tester::Tester(int argc, char **argv) {
  /*
  float slp[] = { 0.0f, 20.0f, 0.0f };
  float specular[] = { 1.0, 1.0, 1.0, 1.0 };
  float shininess[] = { 100.0 };*/

  WinX = 800;
  WinY = 600;
  LeftDown = MiddleDown = RightDown = false;
  MouseX = MouseY = 0;

  // Create the window
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(WinX, WinY);
  glutInitWindowPosition(0, 0);
  WindowHandle = glutCreateWindow(WINDOWTITLE);
  glutSetWindowTitle(WINDOWTITLE);
  glutSetWindow(WindowHandle);

  float specular[] = { 1.0, 1.0, 1.0, 1.0 };
  float shininess[] = { 100.0 };
  float altSpecular[] = { 0.0, 1.0, 0.0, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = { 1.0, 0.0, 0.0, 0.0 };
  GLfloat altlight_position[] = { -1.0, 0.0, 0.0, 0.0 };
  glLoadIdentity();
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  //glLightfv(GL_LIGHT1, GL_POSITION, altlight_position);
  //glLightfv(GL_LIGHT1, GL_DIFFUSE, altSpecular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  //glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHT1);

  // Background color
  glEnable(GL_DEPTH_TEST);
  glClear(GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  //glCullFace(GL_BACK);
  //glEnable(GL_CULL_FACE);
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);

  /*
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, slp);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  */

  // Callbacks
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutSpecialFunc(special);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mousebutton);
  glutMotionFunc(mousemotion);
  glutPassiveMotionFunc(mousemotion);
  glutReshapeFunc(resize);

  // Initialize components
  Cam.SetAspect(float(WinX) / float(WinY));
}

////////////////////////////////////////////////////////////////////////////////

Tester::~Tester() {
  glFinish();
  glutDestroyWindow(WindowHandle);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Update() {
  // Update the components in the world
  Cam.Update();
  clth->update(0.02f);
  //clock_t begin;
  //if (t > 4)
    //t = -4.0f;
  //skel->update();
  //skn->update();
  //Cube.Update();

  // Tell glut to re-display the scene
  glutSetWindow(WindowHandle);
  glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Reset() {
  Cam.Reset();
  Cam.SetAspect(float(WinX) / float(WinY));

  //Cube.Reset();
  //skel->reset();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Draw() {

  // Begin drawing scene
  glViewport(0, 0, WinX, WinY);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw components
  Cam.Draw();		// Sets up projection & viewing matrices
  //Cube.Draw();
  clth->draw();

  // Floor
  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-100.0f, -0.07f, 100.0f);
  glVertex3f(100.0f, -0.07f, 100.0f);
  glVertex3f(100.0f, -0.07f, -100.0f);
  glVertex3f(-100.0f, -0.07f, -100.0f);
  glEnd();

  // Finish drawing scene
  glFinish();
  glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Quit() {
  glFinish();
  glutDestroyWindow(WindowHandle);
  exit(0);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Resize(int x, int y) {
  WinX = x;
  WinY = y;
  Cam.SetAspect(float(WinX) / float(WinY));
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Special(int key, int x, int y) {
  switch(key) {
  case GLUT_KEY_UP:
    //do something here
    break;
  }
}

void Tester::Keyboard(int key, int x, int y) {
  float mov = 0.5f;
  switch (key) {
  case 0x1b:		// Escape
    Quit();
    break;
  case 'r':
    Reset();
    break;
  case 'g':
    clth->g = !clth->g;
    break;
  case 'W':
    if(clth->wind < 20.0f) clth->wind += 1.0f;
    break;
  case 'w':
    if(clth->wind > -20.0f) clth->wind -= 1.0f;
    break;
  case 'x':
    for(int i = 0; i < clth->length; i++)
      clth->pa[clth->length - 1][i]->pos.x -= mov;
    break;
  case 'X':
    for (int i = 0; i < clth->length; i++)
      clth->pa[clth->length - 1][i]->pos.x += mov;
    break;
  case 'y':
    for (int i = 0; i < clth->length; i++)
      if (clth->pa[clth->length - 1][i]->pos.y - mov > 0.0f)
        clth->pa[clth->length - 1][i]->pos.y -= mov;
    break;
  case 'Y':
    for (int i = 0; i < clth->length; i++)
      clth->pa[clth->length - 1][i]->pos.y += mov;
    break;
  case 'z':
    for (int i = 0; i < clth->length; i++)
        clth->pa[clth->length - 1][i]->pos.z -= mov;
    break;
  case 'Z':
    for (int i = 0; i < clth->length; i++)
      clth->pa[clth->length - 1][i]->pos.z += mov;
    break;
  }
}

////////////////////////////////////////////////////////////////////////////////

void Tester::MouseButton(int btn, int state, int x, int y) {
  if (btn == GLUT_LEFT_BUTTON) {
    LeftDown = (state == GLUT_DOWN);
  }
  else if (btn == GLUT_MIDDLE_BUTTON) {
    MiddleDown = (state == GLUT_DOWN);
  }
  else if (btn == GLUT_RIGHT_BUTTON) {
    RightDown = (state == GLUT_DOWN);
  }
}

////////////////////////////////////////////////////////////////////////////////

void Tester::MouseMotion(int nx, int ny) {
  int dx = nx - MouseX;
  int dy = -(ny - MouseY);

  MouseX = nx;
  MouseY = ny;

  // Move camera
  // NOTE: this should really be part of Camera::Update()
  if (LeftDown) {
    const float rate = 1.0f;
    Cam.SetAzimuth(Cam.GetAzimuth() + dx*rate);
    Cam.SetIncline(Cam.GetIncline() - dy*rate);
  }
  if (RightDown) {
    const float rate = 0.01f;
    Cam.SetDistance(Cam.GetDistance()*(1.0f - dx*rate));
  }
}

////////////////////////////////////////////////////////////////////////////////

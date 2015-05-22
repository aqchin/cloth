////////////////////////////////////////
// tester.h
////////////////////////////////////////

#ifndef CSE169_TESTER_H
#define CSE169_TESTER_H

#include "core.h"
#include "camera.h"
#include "cloth.h"
#include "light.h"
#include <ctime>

////////////////////////////////////////////////////////////////////////////////
using namespace std;

class Tester {
public:
  Tester(int argc, char **argv);
  ~Tester();

  void Update();
  void Reset();
  void Draw();

  void Quit();

  // Event handlers
  void Resize(int x, int y);
  void Special(int k, int x, int y);
  void Keyboard(int key, int x, int y);
  void MouseButton(int btn, int state, int x, int y);
  void MouseMotion(int x, int y);

private:
  // Window management
  int WindowHandle;
  int WinX, WinY;

  // Input
  bool LeftDown, MiddleDown, RightDown;
  int MouseX, MouseY;

  // Components
  Camera Cam;
  //SpinningCube Cube;
};

////////////////////////////////////////////////////////////////////////////////

/*
The 'Tester' is a simple top level application class. It creates and manages a
window with the GLUT extension to OpenGL and it maintains a simple 3D scene
including a camera and some other components.
*/

#endif
/*
#pragma once

#include "camera.h"
#include "core.h"
#include "skeleton.h"

class Main {
  Main(int arc, char** argv);
  ~Main();

  void Update();
  void Reset();
  void Draw();

  void Quit();

  // Event handlers
  void Resize(int x, int y);
  void Keyboard(int key, int x, int y);
  void MouseButton(int btn, int state, int x, int y);
  void MouseMotion(int x, int y);

private:
  // Window management
  int WindowHandle;
  int WinX, WinY;

  // Input
  bool LeftDown, MiddleDown, RightDown;
  int MouseX, MouseY;

  // Components
  Camera cam;
  Skeleton skel;
};
*/
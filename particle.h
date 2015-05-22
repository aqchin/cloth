#pragma once

#include "vector3.h"
#include <iostream>
#include <vector>

using namespace std;

class Particle {
public:
  bool isStatic = false;
  vector<Vector3> norms;
  float elas = 0.2f;
  float frict = 0.8f;
  Vector3 pos, vel, acc, f, p;
  float m;

  Particle(): m(1.0f) { pos = vel = acc = f = p = Vector3(); };
  Particle(Vector3 p): pos(p) {};

  void update(float dT) {
    if(!isStatic) {
      acc = (1.0f / m) * f;

      if (pos.y < 0.0f) {
        pos.y = -pos.y;
        vel.y = -elas * vel.y;
        vel.x = (1 - frict) * vel.x;
        vel.z = (1 - frict) * vel.z;
      }

      vel += dT * acc;
      pos += dT * vel;


      p = m * vel;
      f = Vector3(0.0f, 0.0f, 0.0f);
    }
  };
  void Draw() {
  Vector3 norml;
  for (int i = 0; i < norms.size(); i++) {
    norml += norms[i];
    }
  norml = norml / norms.size();
  norml.Normalize();
  glNormal3f(norml.x,norml.y,norml.z);
  glVertex3f(pos.x,pos.y,pos.z);
  }


  void clear() { norms.empty(); };

  void applyForce(Vector3 frc) { if(!isStatic) f += frc; };
};
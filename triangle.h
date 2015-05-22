#pragma once

#include "particle.h"

class Triangle {
private:
  float a_den = 1.2f;
  float drag = 0.4f;
public:
  Particle *p[3];
  Vector3 n_n;

  Triangle(Particle*, Particle*, Particle*);

  void clear();
  void computeForce(Vector3);
  void draw();
};
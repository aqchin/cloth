#pragma once

#include "particle.h"
#include "springdamper.h"
#include "triangle.h"
#include <iostream>
#include <vector>

using namespace std;

class Cloth {
private:
  const Vector3 grav = Vector3(0.0f, -9.81f, 0.0f);
public:
  const int length = 50;
  Particle* pa[50][50];
  vector<Particle*> pts;
  vector<Triangle*> tri;
  vector<SpringDamper*> sd;
  bool g = false;
  float wind = -20.0f;

  Cloth();
  Cloth(Vector3);

  void update(float);
  void draw();
};
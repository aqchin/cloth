#pragma once

#include "particle.h"

class SpringDamper {
public:
  Particle *p1, *p2;
  float sc, df, rl;
  
  SpringDamper();
  SpringDamper(Particle *pa1, Particle *pa2): p1(pa1), p2(pa2), 
    sc(200.0f), df(1.0f) { rl = (pa2->pos - pa1->pos).Mag(); };

  void computeForce();
  void draw();
};
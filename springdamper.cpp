#include "springdamper.h"

void SpringDamper::computeForce() {
  Vector3 e_n = (p2->pos - p1->pos);
  float l = e_n.Mag();
  Vector3 e = (1 / l ) * e_n;

  float v1 = e.Dot(p1->vel);
  float v2 = e.Dot(p2->vel);

  float f = -sc * (rl - l) - df * (v1 - v2);
  Vector3 frc = f * e;

  p1->applyForce(frc);
  p2->applyForce(-frc);
}

void SpringDamper::draw() {
  glBegin(GL_LINES);
  glVertex3f(p1->pos.x, p1->pos.y, p1->pos.z);
  glVertex3f(p2->pos.x, p2->pos.y, p2->pos.z);
  glEnd();
}
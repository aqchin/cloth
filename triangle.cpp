#include "triangle.h"

Triangle::Triangle(Particle* v1, Particle* v2, Particle* v3) {
  p[0] = v1;
  p[1] = v2;
  p[2] = v3;
}

void Triangle::computeForce(Vector3 wind) {
  Vector3 v = (1.0f / 3.0f) * (p[0]->vel + p[1]->vel + p[2]->vel);
  v -= wind;

  n_n.Cross((p[1]->pos - p[0]->pos), (p[2]->pos - p[0]->pos));

  Vector3 nm = n_n;
  nm.Normalize();
  p[0]->norms.push_back(nm);
  p[1]->norms.push_back(nm);
  p[2]->norms.push_back(nm);

  float dot = v.Dot(n_n);
  float prod = (v.Mag() * dot) / (2 * n_n.Mag());

  Vector3 vvan = prod * n_n;
  
  Vector3 force = -(0.5f) * drag * vvan * a_den;
  //force = (1.0f / 3.0f) * force;

  p[0]->applyForce(force);
  p[1]->applyForce(force);
  p[2]->applyForce(force);
}

void Triangle::draw() {
  glBegin(GL_TRIANGLES);
  //n_n.Normalize();
  p[0]->Draw();
  p[1]->Draw();
  p[2]->Draw();
}

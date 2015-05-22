#include "cloth.h"

const float scale = 0.5;
const Vector3 init_vel = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 init_acc = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 init_frc = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 init_momentum = Vector3(0.0f, 0.0f, 0.0f);
const float init_mass = 1.0f;

// Default
Cloth::Cloth() { Cloth::Cloth(Vector3(0.0f, 0.0f, 0.0f)); }

// Set origin
Cloth::Cloth(Vector3 st) {
  Vector3 offset = st - Vector3((float) length / 2, 0.0f, 0.0f);

  // Fill particle array
  for(int r = 0; r < length; r++) {
    for(int c = 0; c < length; c++) {
      pa[r][c] = new Particle(scale * offset + scale * Vector3((float) c, (float) r, -30.0f));
      pa[r][c]->vel = init_vel;
      pa[r][c]->acc = init_acc;
      pa[r][c]->f = init_frc;
      pa[r][c]->m = init_mass;
      pa[r][c]->p = init_momentum;
      pts.push_back(pa[r][c]);

      // Pins
      if((r == length -1))// && (c == 0 || c == length -1))
        pa[r][c]->isStatic = true;
    }
  }

  // Fill triangle vector
  for(int r = 0; r < length; r++) {
    for(int c = 0; c < length; c++) {
      // Bottom row
      if(length > 1 && r == 0 && c < length - 1)
        tri.push_back(new Triangle(pa[r][c], pa[r][c + 1], pa[r + 1][c + 1]));

      // Top row
      else if(length > 1 && r == length - 1 && c < length - 1)
        tri.push_back(new Triangle(pa[r][c], pa[r - 1][c], pa[r][c + 1]));

      // Inside
      else if(length > 2 && r < length -1 && r > 0 && c < length - 1) {
        tri.push_back(new Triangle(pa[r][c], pa[r - 1][c], pa[r][c + 1]));
        tri.push_back(new Triangle(pa[r][c], pa[r][c + 1], pa[r + 1][c + 1]));
      }

      // Add Spring-Dampers
      if(r < length - 1 && c < length - 1) {
        // |_
        sd.push_back(new SpringDamper(pa[r][c], pa[r][c + 1]));
        sd.push_back(new SpringDamper(pa[r][c], pa[r + 1][c]));

        // X
        sd.push_back(new SpringDamper(pa[r][c], pa[r + 1][c + 1]));
        sd.push_back(new SpringDamper(pa[r][c + 1], pa[r + 1][c]));
      }

      // Top row
      if(r == length - 1 && c < length - 1)
        sd.push_back(new SpringDamper(pa[r][c], pa[r][c + 1]));

      // Right column
      if(c == length - 1 && r < length - 1)
        sd.push_back(new SpringDamper(pa[r][c], pa[r + 1][c]));
    }
  }
}

void Cloth::update(float dT) {
  for(vector<Particle*>::iterator it = pts.begin(); it != pts.end(); ++it)
    (*it)->applyForce((*it)->m * grav);

  for(vector<SpringDamper*>::iterator it = sd.begin(); it != sd.end(); ++it)
    (*it)->computeForce();

  for(vector<Triangle*>::iterator it = tri.begin(); it != tri.end(); ++it)
    (*it)->computeForce(Vector3(0.0f, 4.0f, wind));

  for (vector<Particle*>::iterator it = pts.begin(); it != pts.end(); ++it)
    (*it)->update(dT);
}

void Cloth::draw() {
  if(g) {
    glLineWidth(0.01f);
    glDisable(GL_LIGHTING);
    glColor3f(0.0f, 1.0f, 0.0f);
    for (vector<SpringDamper*>::iterator it = sd.begin(); it != sd.end(); ++it)
      (*it)->draw();
    glEnable(GL_LIGHTING);
  }


  glColor3f(1.0f, 1.0f, 0.0f);
  for(vector<Triangle*>::iterator it = tri.begin(); it != tri.end(); ++it) {
    (*it)->draw();
  }

  for (vector<Particle*>::iterator it = pts.begin(); it != pts.end(); ++it)
    (*it)->norms.clear();
}
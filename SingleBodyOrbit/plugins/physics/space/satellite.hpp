#pragma once

#include "util.hpp"
#include "communication.hpp"

#include <map>
#include <queue>
#include <string>

#include <ode/ode.h>
#include <plugins/physics.h>

class PhysicsObject {
protected:
  std::string name;

  dGeomID geom;
  dBodyID body;

  double thrusterForce;

public:
  PhysicsObject(const std::string name);

  dGeomID getGeom();
  dBodyID getBody();
  double getMass();
  double getVelocity(); // TODO
  const double *getPosition();

  void printInfo();

  void setMass(double mass);
  void setForce(double x, double y, double z);
  void setLinearVel(double x, double y, double z);

  void addForce(double x, double y, double z);
};

class Thruster {
private:
  double force;
  double maxForce;

public:
  Thruster(const double maxForce);
  void setForce(double force);
  double getForce();
};

class satellite : public PhysicsObject {
private:
  communicator communicator;

public:
  satellite(const std::string name);
  void tick();
};
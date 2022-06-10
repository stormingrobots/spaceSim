#pragma once

#include "Util.hpp"

#include <ode/ode.h>
#include <plugins/physics.h>
#include <queue>
#include <string>

#define MESSAGE_DELIMITER '!'

class PhysicsObject {
protected:
  std::string name;

  dGeomID geom;
  dBodyID body;

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

class Communicator {
private:
  std::string buffer;
  std::queue<std::string> messageQueue;

public:
  Communicator();
  void send(int channel, std::string message);
  void receive();
  std::string next();
};

class Thruster {
private:
  double force;
  double maxForce;

public:
  Thruster(const double maxForce);
  void setForce(double force);
};

class Satellite : public PhysicsObject {
private:
  Thruster thruster = Thruster(10);
  Communicator communicator;

public:
  Satellite(const std::string name);
  void tick();
};
#pragma once

#include "packet.hpp"
#include "util.hpp"

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
  double getForce();
};

class Satellite : public PhysicsObject {
private:
  Communicator communicator;
  std::map<std::string, Thruster *> thrusters;

public:
  Satellite(const std::string name);
  void tick();
};
#include "satellite.hpp"

PhysicsObject::PhysicsObject(std::string name) {
  this->name = name;
  geom = dWebotsGetGeomFromDEF(name.c_str());
  body = dGeomGetBody(geom);

  dBodySetGravityMode(body, 0);
}

dGeomID PhysicsObject::getGeom() { return geom; }

dBodyID PhysicsObject::getBody() { return body; }

double PhysicsObject::getMass() {
  dMass mass;
  dBodyGetMass(body, &mass);
  return mass.mass;
}

const double *PhysicsObject::getPosition() { return dBodyGetPosition(body); }

void PhysicsObject::printInfo() {
  log("[Physics] [%s] %p %p\n", name.c_str(), geom, body);
}

void PhysicsObject::setMass(double val) {
  dMass mass;
  dBodyGetMass(body, &mass);
  mass.mass = val;
  dBodySetMass(body, &mass);
}

void PhysicsObject::setForce(double x, double y, double z) {
  dBodySetForce(body, x, y, z);
}

void PhysicsObject::addForce(double x, double y, double z) {
  dBodyAddForce(body, x, y, z);
}

void PhysicsObject::setLinearVel(double x, double y, double z) {
  dBodySetLinearVel(body, x, y, z);
}

satellite::satellite(const std::string name) : PhysicsObject(name) {
//   thrusters["alpha"] = new Thruster(10);
//   thrusters["beta"] = new Thruster(10);
//   thrusters["gamma"] = new Thruster(10);
//   thrusters["delta"] = new Thruster(10);
}

void satellite::tick() {
  communicator.poll();
  communicator.sendPing();
}

Thruster::Thruster(const double maxForce) { this->maxForce = maxForce; }

void Thruster::setForce(double force) {
  this->force = clamp(force, 0, maxForce);
}

double Thruster::getForce() { return force; }
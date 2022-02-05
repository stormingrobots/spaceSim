#include "Util.hpp"

double norm(const double* pos) {
  return sqrt(
    pos[0] * pos[0] +
    pos[1] * pos[1] +
    pos[2] * pos[2]);
}

PhysicsObject::PhysicsObject(const char* name) {
  this->name = name;
  geom = dWebotsGetGeomFromDEF(name);
  body = dGeomGetBody(geom);

  dBodySetGravityMode(body, 0);
}

dGeomID PhysicsObject::getGeom() {
  return geom;
}

dBodyID PhysicsObject::getBody() {
  return body;
}

double PhysicsObject::getMass() {
  dMass mass;
  dBodyGetMass(body, &mass);
  return mass.mass;
}

const double* PhysicsObject::getPosition() {
  return dBodyGetPosition(body);
}

void PhysicsObject::printInfo() {
  dWebotsConsolePrintf("%s: %p %p\n", name, geom, body);
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

void PhysicsObject::setLinearVel(double x, double y, double z) {
  dBodySetLinearVel(body, x, y, z);
}
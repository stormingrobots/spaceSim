#include "satellite.hpp"

std::string physics_radio::readData() {
  int bytes = 0;
  const void* data = dWebotsReceive(&bytes);
  return std::string((char*)data, bytes);
}

void physics_radio::sendData(const void* data, int size) {
  dWebotsSend(EMITTER_CHANNEL, data, size);
}

void physics_radio::onPing() {
  log("[Radio] Ping recieved!");
  sendPing();
}

physics_object::physics_object(std::string name) {
  this->name = name;
  geom = dWebotsGetGeomFromDEF(name.c_str());
  body = dGeomGetBody(geom);

  dBodySetGravityMode(body, 0);
}

dGeomID physics_object::getGeom() { return geom; }

dBodyID physics_object::getBody() { return body; }

double physics_object::getMass() {
  dMass mass;
  dBodyGetMass(body, &mass);
  return mass.mass;
}

const double *physics_object::getPosition() { return dBodyGetPosition(body); }

void physics_object::printInfo() {
  log("[Physics] [%s] %p %p\n", name.c_str(), geom, body);
}

void physics_object::setMass(double val) {
  dMass mass;
  dBodyGetMass(body, &mass);
  mass.mass = val;
  dBodySetMass(body, &mass);
}

void physics_object::setForce(double x, double y, double z) {
  dBodySetForce(body, x, y, z);
}

void physics_object::addForce(double x, double y, double z) {
  dBodyAddForce(body, x, y, z);
}

void physics_object::setLinearVel(double x, double y, double z) {
  dBodySetLinearVel(body, x, y, z);
}

satellite::satellite(const std::string name) : physics_object(name) {
//   thrusters["alpha"] = new Thruster(10);
//   thrusters["beta"] = new Thruster(10);
//   thrusters["gamma"] = new Thruster(10);
//   thrusters["delta"] = new Thruster(10);
}

void satellite::tick() {
  radio.poll();
}
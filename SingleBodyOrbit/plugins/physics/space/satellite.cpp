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
  // sendPing();
}

void physics_radio::onThrustSet(thrust_set_body data) {
  log("[Radio] Thruster %d set to %f", data.id, data.thrust);
  parent.getThruster(data.id).setThrust(data.thrust);
}

physics_radio::physics_radio(satellite& parent) : parent(parent) {}

physics_object::physics_object() {}

void physics_object::init(std::string name) {
  this->name = name;
  geom = dWebotsGetGeomFromDEF(name.c_str());
  body = dGeomGetBody(geom);

  dBodySetGravityMode(body, 0);
}

std::string& physics_object::getName() { return name; }

dGeomID physics_object::getGeom() { return geom; }

dBodyID physics_object::getBody() { return body; }

double physics_object::getMass() {
  dMass mass;
  dBodyGetMass(body, &mass);
  return mass.mass;
}

vec3d physics_object::getPosition() {
  const double* pos = dBodyGetPosition(body);
  return { pos[0], pos[1], pos[2] };
}

void physics_object::printInfo() {
  log("[Physics] [%s] %p %p\n", name.c_str(), geom, body);
}

void physics_object::setMass(double val) {
  dMass mass;
  dBodyGetMass(body, &mass);
  mass.mass = val;
  dBodySetMass(body, &mass);
}

void physics_object::setForce(vec3d force) {
  dBodySetForce(body, force.x, force.y, force.z);
}

void physics_object::setLinearVelocity(vec3d velocity) {
  dBodySetLinearVel(body, velocity.x, velocity.y, velocity.z);
}

void physics_object::addForce(vec3d force) {
  dBodyAddForce(body, force.x, force.y, force.z);
}

void physics_object::addRelForce(vec3d offset, vec3d force) {
  dBodyAddRelForceAtRelPos(body, force.x, force.y, force.z, offset.x, offset.y, offset.z);
}

void physics_object::applyGravity(physics_object& object) {
  vec3d radius = getPosition() - object.getPosition();
  double dist = radius.norm() * 1000; // km -> m
  vec3d force = radius *
    (GRAVITATIONAL_CONSTANT * getMass() * object.getMass() / (dist * dist * dist));
  object.addForce(force);
}

physics_thruster::physics_thruster(satellite& parent, int id, vec3d offset, vec3d direction) :
  parent(parent), id(id), offset(offset), direction(direction.unit()), thrust(0) {
}

double physics_thruster::getThrust() { return thrust; }

int physics_thruster::getId() { return id; }

vec3d physics_thruster::getForce() { return direction * thrust; }

vec3d physics_thruster::getOffset() { return offset; }

void physics_thruster::setThrust(double thrust) {
  this->thrust = thrust;
}

satellite::satellite() : satelliteRadio(*this) {
  for (int i = 0; i < 20; i++)
    thrusters.push_back(physics_thruster(*this, i, { 0, 0, 0 }, { 1, 1, 1 }));
}

void satellite::init(const std::string& name) {
  physics_object::init(name);
}

void satellite::tick() {
  satelliteRadio.poll();

  //thrust
  for (auto& thruster : thrusters) {
    addRelForce(thruster.getOffset(), thruster.getForce());
  }
}

thruster& satellite::getThruster(int id) {
  return thrusters[id];
}
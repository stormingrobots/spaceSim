#include "Satellite.hpp"

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
  dWebotsConsolePrintf("%s: %p %p\n", name.c_str(), geom, body);
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

Satellite::Satellite(const std::string name) : PhysicsObject(name) {
  thrusters["alpha"] = new Thruster(10);
  thrusters["beta"] = new Thruster(10);
  thrusters["gamma"] = new Thruster(10);
  thrusters["delta"] = new Thruster(10);
}

void Satellite::tick() {
  communicator.receive();
  std::string msg;

  while (!(msg = communicator.next()).empty()) {
    int temp = msg.find(",");
    std::string packetName = msg.substr(0, temp);
    std::string contents = msg.substr(temp + 1, msg.length() - temp - 1);

    if (packetName == "SET_THRUST") {
      SetThrustPacket packet(contents);
      thrusters[packet.getName()]->setForce(packet.getThrust());
    }
  }

  dWebotsConsolePrintf("Alpha: %.2f\n", thrusters["alpha"]->getForce());
  dWebotsConsolePrintf("Beta: %.2f\n", thrusters["beta"]->getForce());
  dWebotsConsolePrintf("Gamma: %.2f\n", thrusters["gamma"]->getForce());
  dWebotsConsolePrintf("Delta: %.2f\n", thrusters["delta"]->getForce());
}

Communicator::Communicator() {}

void Communicator::send(int channel, std::string message) {
  std::string content = message;
  content.push_back(MESSAGE_DELIMITER);
  dWebotsSend(channel, content.c_str(), content.length());
}

void Communicator::receive() {
  int size = 0;
  const char *data = (const char *)dWebotsReceive(&size);
  buffer.append(data, size);

  std::size_t lastPos = 0;
  std::size_t pos = 0;
  while ((pos = buffer.find(MESSAGE_DELIMITER, lastPos)) != std::string::npos) {
    messageQueue.push(buffer.substr(lastPos, pos - lastPos));
    lastPos = pos + 1;
  }
  buffer = buffer.substr(lastPos);
}

std::string Communicator::next() {
  std::string res;
  if (!messageQueue.empty()) {
    res = messageQueue.front();
    messageQueue.pop();
  }
  return res;
}

Thruster::Thruster(const double maxForce) { this->maxForce = maxForce; }

void Thruster::setForce(double force) {
  this->force = clamp(force, 0, maxForce);
}

double Thruster::getForce() { return force; }
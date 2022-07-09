#include "Satellite.hpp"

Thruster::Thruster(Communicator *communicator, std::string name) {
  this->communicator = communicator;
  this->name = name;
}

void Thruster::setThrust(double thrust) {
  this->thrust = thrust;
  std::ostringstream msg;
  msg << "SET_THRUST," << name << "," << thrust;
  communicator->send(msg.str());
}

double Thruster::getThrust() { return this->thrust; }

Satellite::Satellite(webots::Robot *robot) {
  webots::Emitter *emitter = robot->getEmitter("emitter");
  webots::Receiver *receiver = robot->getReceiver("receiver");

  this->communicator = new Communicator(emitter, receiver);
  this->thruster = new Thruster(communicator, "thruster");
}

Communicator *Satellite::getCommunicator() { return this->communicator; }

Thruster *Satellite::getThruster() { return this->thruster; }
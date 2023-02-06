#include "satellite.hpp"

Thruster::Thruster(Communicator *communicator, std::string name) {
  this->communicator = communicator;
  this->name = name;
}

void Thruster::setThrust(double thrust) {
  this->thrust = thrust;
  std::ostringstream msg;
  msg << "SET_THRUST," << name << "," << thrust;
  communicator->send(msg.str());

  // debug for displaying communication messages
  // std::cout << msg.str() << std::endl;
}

double Thruster::getThrust() { return this->thrust; }

Satellite::Satellite(webots::Robot *robot) {
  webots::Emitter *emitter = robot->getEmitter("emitter");
  webots::Receiver *receiver = robot->getReceiver("receiver");

  this->communicator = new Communicator(emitter, receiver);
  thrusters["alpha"] = new Thruster(communicator, "alpha");
  thrusters["beta"] = new Thruster(communicator, "beta");
  thrusters["gamma"] = new Thruster(communicator, "gamma");
  thrusters["delta"] = new Thruster(communicator, "delta");
}

Communicator *Satellite::getCommunicator() { return this->communicator; }

Thruster *Satellite::getThruster(std::string name) {
  return this->thrusters[name];
}
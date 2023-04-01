#include "satellite.hpp"

satellite_radio::satellite_radio(webots::Emitter* emitter, webots::Receiver* receiver) {
  this->emitter = emitter;
  this->receiver = receiver;

  emitter->setChannel(EMITTER_CHANNEL);
  receiver->setChannel(RECEIVER_CHANNEL);
  receiver->enable(RECEIVER_SAMPLING_PERIOD);
}

satellite_radio::satellite_radio() {
  emitter = nullptr;
  receiver = nullptr;
}

std::string satellite_radio::readData() {
  if (receiver->getQueueLength() != 0)
    return std::string((char*)receiver->getData(), receiver->getDataSize());
  return "";
}

void satellite_radio::sendData(const void* data, int size) {
  emitter->send(data, size);
}

void satellite_radio::onPing() {
  std::cout << "[Satellite] Received Ping!" << std::endl;
  // sendPing();
}

void satellite_radio::onThrustSet(thrust_set_body data) {
  std::cout << "[Satellite] Unsupported Method: thrust_set" << std::endl;
}

satellite_thruster::satellite_thruster(int id, satellite& parent) :
  id(id), parent(parent) {
}

void satellite_thruster::setThrust(double thrust) {
  this->thrust = thrust;
  std::cout << "[Satellite] Setting Thruster #" << id << " to " << thrust << std::endl;
  parent.getRadio().setThrust(id, thrust);
}

double satellite_thruster::getThrust() {
  return thrust;
}

int satellite_thruster::getId() {
  return id;
}

satellite::satellite(webots::Robot& robot) {
  webots::Emitter* emitter = robot.getEmitter("emitter");
  webots::Receiver* receiver = robot.getReceiver("receiver");
  satelliteRadio = satellite_radio(emitter, receiver);

  for (int i = 0; i < 20; i++)
    thrusters.push_back(satellite_thruster(i, *this));

  satelliteRadio.sendPing();
}

void satellite::tick() {
  satelliteRadio.poll();
}

radio& satellite::getRadio() {
  return satelliteRadio;
}

thruster& satellite::getThruster(int id) {
  return thrusters[id];
}
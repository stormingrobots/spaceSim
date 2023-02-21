#include "satellite.hpp"

satellite_radio::satellite_radio(webots::Emitter* emitter, webots::Receiver* receiver) {
  this->emitter = emitter;
  this->receiver = receiver;

  emitter->setChannel(EMITTER_CHANNEL);
  receiver->setChannel(RECEIVER_CHANNEL);
  receiver->enable(RECEIVER_SAMPLING_PERIOD);
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
  sendPing();
}

satellite::satellite(webots::Robot* robot) {
  webots::Emitter* emitter = robot->getEmitter("emitter");
  webots::Receiver* receiver = robot->getReceiver("receiver");
  radio = new satellite_radio(emitter, receiver);

  radio->sendPing();
}

void satellite::tick() {
  radio->poll();
}
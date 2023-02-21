#include "satellite.hpp"

satellite::satellite(webots::Robot* robot) {
  webots::Emitter* emitter = robot->getEmitter("emitter");
  webots::Receiver* receiver = robot->getReceiver("receiver");
  comms = new communicator(emitter, receiver);
}

void satellite::tick() {
  comms->poll();
}
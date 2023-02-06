#pragma once

#include <webots/Emitter.hpp>
#include <webots/Receiver.hpp>
#include <webots/Robot.hpp>

#include <queue>
#include <string>

#define MESSAGE_DELIMITER '!'

class Communicator {
private:
  std::string buffer;
  std::queue<std::string> messageQueue;

  webots::Emitter *emitter;
  webots::Receiver *receiver;

public:
  Communicator(webots::Emitter *emitter, webots::Receiver *receiver);
  void send(std::string message);
  void receive();
  std::string next();
};
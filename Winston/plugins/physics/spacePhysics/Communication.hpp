#pragma once

#include <plugins/physics.h>

#include <queue>
#include <string>

#define MESSAGE_DELIMITER '.'

class Communicator {
private:
  std::string buffer;
  std::queue<std::string> messageQueue;

public:
  Communicator();
  void send(int channel, std::string message);
  void receive();
  std::string next();
};
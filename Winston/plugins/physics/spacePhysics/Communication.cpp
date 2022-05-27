#include "Communication.hpp"

Communicator::Communicator() {
  // stuff
}

void Communicator::send(int channel, std::string message) {
  dWebotsSend(channel, message.c_str(), message.length());
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
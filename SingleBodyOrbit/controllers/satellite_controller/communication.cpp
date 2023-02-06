#include "communication.hpp"

Communicator::Communicator(webots::Emitter *emitter,
                           webots::Receiver *receiver) {
  this->emitter = emitter;
  this->receiver = receiver;

  receiver->setChannel(1);
  emitter->setChannel(0);
}

void Communicator::send(std::string message) {
  std::string content = message;
  content.push_back(MESSAGE_DELIMITER);
  emitter->send(content.c_str(), content.length());
}

void Communicator::receive() {
  int size = receiver->getDataSize();
  const char *data = (const char *)receiver->getData();
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
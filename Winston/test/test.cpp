#include <queue>
#include <string>

#include <iostream>

#define MESSAGE_DELIMITER '.'

std::string buffer = "";
std::queue<std::string> messageQueue;

void receive(std::string message) {
  buffer.append(message);

  std::size_t lastPos = 0;
  std::size_t pos = 0;

  while ((pos = buffer.find(MESSAGE_DELIMITER, lastPos)) != -1) {
    messageQueue.push(buffer.substr(lastPos, pos - lastPos));
    lastPos = pos + 1;
  }

  buffer = buffer.substr(lastPos);
}

std::string next() {
  std::string msg = messageQueue.front();
  messageQueue.pop();
  return msg;
}

int main() {

  receive("message1|");

  std::cout << next() << std::endl;

  receive("message2|message3|");
  std::cout << next() << std::endl;
  std::cout << next() << std::endl;
}
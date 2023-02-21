#pragma once

#include <cstdint>
#include <string>

#define PING_PACKET 0x01

struct packet_header {
  uint8_t magic = 0x29;
  uint8_t type;
};

class radio {
private:
  std::string buffer;

  template <typename T>
  void sendBlock(T block);
  void sendHeader(uint8_t type);

  template<typename T>
  T readBlock();

protected:
  virtual std::string readData() = 0; // read data from receiver
  virtual void sendData(const void* data, int size) = 0; // send data to emitter

  // what to do when certain packets are recieved
  // ensure body data is passed on for more complex packets
  virtual void onPing() = 0;

public:
  void poll();

  void sendPing();
};
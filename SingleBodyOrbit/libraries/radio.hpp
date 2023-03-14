#pragma once

#include "packets.hpp"

#include <string>

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
  virtual void onThrustSet(thrust_set_body data) = 0;

public:
  void poll();

  void sendPing();
  void setThrust(unsigned char id, double thrust);
};
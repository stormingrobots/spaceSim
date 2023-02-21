#pragma once

#include <cstdint>
#include <string>

#include <ode/ode.h>
#include <plugins/physics.h>
#include <util.hpp>

#define RECEIVER_SAMPLING_PERIOD 1
#define RECEIVER_CHANNEL 0
#define EMITTER_CHANNEL 1

#define PING_PACKET 0x01

struct packet_header {
  uint8_t magic = 0x29;
  uint8_t type;
};

class communicator {
private:
  std::string buffer;

  template <typename T>
  void sendBlock(T block);
  void sendHeader(uint8_t type);

  template<typename T>
  T readBlock();

public:
  void sendPing();
  void poll();
};
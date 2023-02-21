#pragma once

#include <cstdint>
#include <iostream>

#include <webots/Emitter.hpp>
#include <webots/Receiver.hpp>

#define RECEIVER_SAMPLING_PERIOD 1
#define RECEIVER_CHANNEL 1
#define EMITTER_CHANNEL 0

#define PING_PACKET 0x01

struct packet_header {
  uint8_t magic = 0x29;
  uint8_t type;
};

class communicator {
private:
  std::string buffer;
  webots::Emitter* emitter;
  webots::Receiver* receiver;

  template <typename T>
  void sendBlock(T block);
  void sendHeader(uint8_t type);

  template<typename T>
  T readBlock();

public:
  communicator(webots::Emitter* emitter, webots::Receiver* receiver);

  void sendPing();
  void poll();
};
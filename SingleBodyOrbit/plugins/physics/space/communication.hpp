#pragma once

#include <cstdint>

#include <ode/ode.h>
#include <plugins/physics.h>

typedef struct packet_header {
  uint8_t magic = 29;
  uint8_t type;
};

class Communicator {
private:
  void sendPacket(int channel, uint8_t type, char* data);

public:
  Communicator();

};
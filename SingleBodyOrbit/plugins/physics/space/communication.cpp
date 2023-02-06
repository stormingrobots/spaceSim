#include "communication.hpp"

void Communicator::sendPacket(int channel, uint8_t type, char* data) {

  packet_header header{ type };
  dWebotsSend(channel, (char*)&header, int(sizeof(packet_header)));
}
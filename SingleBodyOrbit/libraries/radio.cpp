#include "radio.hpp"

template <typename T>
void radio::sendBlock(T block) {
  sendData((char*)&block, int(sizeof(block)));
}

void radio::sendHeader(uint8_t type) {
  packet_header header;
  header.type = type;
  sendBlock<packet_header>(header);
}

template <typename T>
T radio::readBlock() {
  T block;
  if(buffer.size() < sizeof(block)) return block; // return empty block, incomplete packet
  memcpy(&block, buffer.data(), sizeof(block));
  buffer = buffer.substr(sizeof(block));
  return block;
}

void radio::poll() {
  buffer += readData();

  //read buffer for packet header
  if (buffer.size() >= sizeof(packet_header)) {
    packet_header header = readBlock<packet_header>();
    if (header.magic != 0x29) {
      buffer.clear();
      return;
    }

    switch (header.type) {
    case PING_PACKET:
      onPing();
      break;

    case THRUST_SET_REQUEST:
      onThrustSet(readBlock<thrust_set_body>());
      break;
    }
  }
}

void radio::sendPing() {
  sendHeader(PING_PACKET);
}

void radio::setThrust(unsigned char id, double thrust) {
  thrust_set_body body;
  body.id = id;
  body.thrust = thrust;

  sendHeader(THRUST_SET_REQUEST);
  sendBlock<thrust_set_body>(body);
}
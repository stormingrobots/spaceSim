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
    case PING_PACKET: onPing(); break;
    }
  }
}

void radio::sendPing() {
  sendHeader(PING_PACKET);
}

#include "communication.hpp"

template <typename T>
void communicator::sendBlock(T block) {
  dWebotsSend(EMITTER_CHANNEL, (char*)&block, int(sizeof(block)));
}

void communicator::sendHeader(uint8_t type) {
  packet_header header;
  header.type = type;
  sendBlock<packet_header>(header);
}

template <typename T>
T communicator::readBlock() {
  T block;
  memcpy(&block, buffer.data(), sizeof(block));
  buffer = buffer.substr(sizeof(block));
  return block;
}

void communicator::sendPing() {
  sendHeader(PING_PACKET);
  log("[Physics] Sent ping");
}

void communicator::poll() {
  int bytes = 0;
  const void* data = dWebotsReceive(&bytes);
  buffer.append((char*)data, bytes);

  if (buffer.size() >= sizeof(packet_header)) {
    packet_header header = readBlock<packet_header>();
    if (header.magic != 0x29) {
      log("[Physics] Invalid magic");
      buffer.clear();
      return;
    }

    switch (header.type) {
    case PING_PACKET:
      log("[Physics] Received ping");
      break;
    default:
      log("[Physics] Invalid packet type");
      break;
    }
  }
}
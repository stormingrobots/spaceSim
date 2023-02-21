#include "communication.hpp"

template <typename T>
void communicator::sendBlock(T block) {
  emitter->send((char*)&block, int(sizeof(block)));
}

void communicator::sendHeader(uint8_t type) {
  packet_header header;
  header.type = type;
  sendBlock<packet_header>(header);
}

void communicator::sendPing() {
  sendHeader(PING_PACKET);
}

template <typename T>
T communicator::readBlock() {
  T block;
  memcpy(&block, buffer.data(), sizeof(block));
  buffer = buffer.substr(sizeof(block));
  return block;
}

void communicator::poll() {
  if (receiver->getQueueLength() != 0)
    buffer.append((char*)receiver->getData(), receiver->getDataSize());

  //read buffer for packet header
  if (buffer.size() >= sizeof(packet_header)) {
    packet_header header = readBlock<packet_header>();
    if (header.magic != 0x29) {
      buffer.clear();
      return;
    }

    switch (header.type) {
    case PING_PACKET:
      std::cout << "[Satellite] Received ping" << std::endl;
      break;
    }
  }
}

communicator::communicator(webots::Emitter* emitter, webots::Receiver* receiver) {
  this->emitter = emitter;
  this->receiver = receiver;

  receiver->setChannel(RECEIVER_CHANNEL);
  receiver->enable(RECEIVER_SAMPLING_PERIOD);
  emitter->setChannel(EMITTER_CHANNEL);

  std::cout << "[Satellite] Communicator Active" << std::endl;
}
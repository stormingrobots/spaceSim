#include <string>
#include <iostream>

std::string buffer;

// Debug

inline unsigned int to_uint(char ch) {
  return static_cast<unsigned int>(static_cast<unsigned char>(ch));
}

void print_buffer() {
  std::cout << "Buffer Data: " << std::hex;
  for (char ch : buffer) {
    std::cout << "0x" << to_uint(ch) << ' ';
  }
  std::cout << std::endl << std::dec;
}

// Structs

#define PING_PACKET 0x01
#define THRUSTER_CONTROL_PACKET 0x02

struct packet_header {
  uint8_t magic = 0x29;
  uint8_t type;
};

struct thruster_control_packet {
  uint8_t thruster;
  uint8_t speed;
};

//Sending

template <typename T>
void send_block(T block) {
  buffer.append(reinterpret_cast<char*>(&block), sizeof(block));
}

void send_header(uint8_t type) {
  packet_header header;
  header.type = type;
  send_block<packet_header>(header);
}

// actual api sends
//send thruster control packet
void send_thruster_control(uint8_t thruster, uint8_t speed) {
  send_header(THRUSTER_CONTROL_PACKET);

  thruster_control_packet packet;
  packet.thruster = thruster;
  packet.speed = speed;
  send_block<thruster_control_packet>(packet);
}

//Receiving
template <typename T>
T read_block() {
  T block;
  memcpy(&block, buffer.data(), sizeof(block));
  buffer = buffer.substr(sizeof(block));
  return block;
}

void poll() {
  //...
  if (buffer.size() >= sizeof(packet_header)) {
    packet_header header = read_block<packet_header>();

    if (header.magic != 0x29) {
      std::cout << "Invalid magic!" << std::endl;
      return;
    }

    switch (header.type) {
    case PING_PACKET:
      std::cout << "Ping packet received!" << std::endl;
      break;

    case THRUSTER_CONTROL_PACKET:
      if (buffer.size() >= sizeof(thruster_control_packet)) {
        thruster_control_packet packet = read_block<thruster_control_packet>();
        std::cout << "Thruster control packet received! Thruster: " << (int)packet.thruster << " Speed: " << (int)packet.speed << std::endl;
      }
      break;
    }
  }
}

int main() {

  send_header(PING_PACKET);
  print_buffer();

  poll();
  print_buffer();

  send_thruster_control(1, 100);
  print_buffer();

  poll();
  print_buffer();
}
#include "Packet.hpp"

Packet::Packet(std::string raw) { this->raw = raw; }

std::string Packet::next() {
  std::size_t pos = raw.find(PARAMETER_DELIMITER);
  std::string content;

  if (pos == std::string::npos) {
    content = raw;
    this->raw = "";
  } else {
    content = raw.substr(0, pos);
    this->raw = raw.substr(pos + 1, raw.length() - pos - 1);
  }

  return content;
}

SetThrustPacket::SetThrustPacket(std::string raw) : Packet(raw) {
  this->thruster_name = next();
  this->thrust = std::stod(next());
}

std::string SetThrustPacket::get_name() { return this->thruster_name; }
double SetThrustPacket::get_thrust() { return this->thrust; }
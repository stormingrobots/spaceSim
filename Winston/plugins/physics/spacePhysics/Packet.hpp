#pragma once

#include <string>

#define MESSAGE_DELIMITER '!'
#define PARAMETER_DELIMITER ','

class Packet {
private:
  std::string raw;

public:
  Packet(std::string raw);
  std::string next();
};

class SetThrustPacket : public Packet {
private:
  std::string thruster_name;
  double thrust;

public:
  SetThrustPacket(std::string raw);

  std::string get_name();
  double get_thrust();
};
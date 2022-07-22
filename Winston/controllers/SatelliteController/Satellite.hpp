#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include <webots/Emitter.hpp>
#include <webots/Receiver.hpp>
#include <webots/Robot.hpp>

#include "SatelliteCommunication.hpp"

class Thruster {
private:
  Communicator *communicator;
  std::string name;
  double thrust = 0;

public:
  Thruster(Communicator *communicator, std::string name);
  void setThrust(double thrust);
  double getThrust();
};

class Satellite {
private:
  Communicator *communicator;
  std::map<std::string, Thruster *> thrusters;

public:
  Satellite(webots::Robot *robot);
  Communicator *getCommunicator();
  Thruster *getThruster(std::string name);
};
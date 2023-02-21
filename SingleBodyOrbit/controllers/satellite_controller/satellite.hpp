#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include <webots/Emitter.hpp>
#include <webots/Receiver.hpp>
#include <webots/Robot.hpp>

#include "communication.hpp"

class satellite {
private:
  communicator* comms;

public:
  satellite(webots::Robot* robot);
  void tick();
};
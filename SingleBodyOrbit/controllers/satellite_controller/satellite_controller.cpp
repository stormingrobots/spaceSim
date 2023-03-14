// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>

#include <iostream>
#include <string>

#include "satellite.hpp"

using namespace webots;

int main(int argc, char** argv) {
  webots::Robot* robot = new webots::Robot();
  satellite satellite(robot);
  int timeStep = (int)robot->getBasicTimeStep();

  std::cout << "[Satellite] Starting spaceship with timestep: " << timeStep << std::endl;

  int counter = 0;

  while (robot->step(timeStep) != -1) {
    satellite.tick();

    counter = (counter + 1) % 20;

    satellite.getThruster(counter)->setThrust(rand() / (double(RAND_MAX)));
  }

  delete robot;
  return 0;
}

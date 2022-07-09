// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Emitter.hpp>
#include <webots/Receiver.hpp>
#include <webots/Robot.hpp>

#include <iostream>
#include <string>

#include "Satellite.hpp"
#include "SatelliteCommunication.hpp"

using namespace webots;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  Satellite *sa = new Satellite(robot);
  Thruster *thruster = sa->getThruster();

  int timeStep = (int)robot->getBasicTimeStep();

  std::cout << "Starting spaceship with timestep: " << timeStep << std::endl;

  double counter = 10;
  while (robot->step(timeStep) != -1) {
    thruster->setThrust(counter);
  }

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}

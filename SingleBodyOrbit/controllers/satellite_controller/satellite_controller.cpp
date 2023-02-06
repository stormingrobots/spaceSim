// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Emitter.hpp>
#include <webots/Receiver.hpp>
#include <webots/Robot.hpp>

#include <iostream>
#include <string>

#include "satellite.hpp"
#include "communication.hpp"
 
using namespace webots;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  Satellite *sa = new Satellite(robot);
  Thruster *thrusterAlpha = sa->getThruster("alpha");
  Thruster *thrusterBeta = sa->getThruster("beta");
  Thruster *thrusterGamma = sa->getThruster("gamma");
  Thruster *thrusterDelta = sa->getThruster("delta");

  int timeStep = (int)robot->getBasicTimeStep();

  std::cout << "Starting spaceship with timestep: " << timeStep << std::endl;

  while (robot->step(timeStep) != -1) {
    thrusterAlpha->setThrust(5);
    thrusterBeta->setThrust(10);
    thrusterGamma->setThrust(1000);
    thrusterDelta->setThrust(-10);
  }

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}

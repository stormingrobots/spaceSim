// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Emitter.hpp>
#include <webots/Receiver.hpp>
#include <webots/Robot.hpp>

#include <iostream>
#include <string>
#include <cstring>

using namespace webots;

int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();
  Emitter *emitter = robot->getEmitter("emitter");
  Receiver *receiver = robot->getReceiver("receiver");

  receiver->setChannel(1);

  std::string message = "Hello World.";
  emitter->setChannel(0);
  int timeStep = (int)robot->getBasicTimeStep();

  std::cout << "Starting spaceship with timestep: " << timeStep << std::endl;
  // std::cout << "Message: " << message.c_str() << std::endl;
  // std::cout << "Message Length: " << std::strlen(message.c_str()) << std::endl;
  
  while (robot->step(timeStep) != -1) {
    // std::cout << "Thruster Velocity: " << thruster->getVelocity() <<
    // std::endl;
    
    emitter->send(message.c_str(), message.length());
  }

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}

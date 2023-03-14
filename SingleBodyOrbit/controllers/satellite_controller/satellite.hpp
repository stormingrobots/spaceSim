#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <webots/Emitter.hpp>
#include <webots/Receiver.hpp>
#include <webots/Robot.hpp>

#include "radio.hpp"
#include "interfaces.hpp"

#define RECEIVER_SAMPLING_PERIOD 1
#define RECEIVER_CHANNEL 1
#define EMITTER_CHANNEL 0

class satellite_radio : public radio {
private:
  webots::Emitter* emitter;
  webots::Receiver* receiver;

protected:
  std::string readData() override;
  void sendData(const void* data, int size) override;

  void onPing() override;
  void onThrustSet(thrust_set_body data) override;

public:
  satellite_radio(webots::Emitter* emitter, webots::Receiver* receiver);
};

class satellite_thruster : public thruster {
private:
  int id;
  double thrust;
  satellite* parent;

public:
  satellite_thruster(int id, satellite* parent);
  void setThrust(double thrust) override;
  double getThrust() override;
  int getId() override;
};

class satellite {
private:
  radio* satelliteRadio;
  std::vector<thruster*> thrusters;

public:
  satellite(webots::Robot* robot);
  void tick();
  
  radio* getRadio();
  thruster* getThruster(int id);
};
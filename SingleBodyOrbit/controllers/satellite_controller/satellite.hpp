#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include <webots/Emitter.hpp>
#include <webots/Receiver.hpp>
#include <webots/Robot.hpp>

#include "radio.hpp"

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

public:
  satellite_radio(webots::Emitter* emitter, webots::Receiver* receiver);
};

class satellite {
private:
  radio* radio;

public:
  satellite(webots::Robot* robot);
  void tick();
};
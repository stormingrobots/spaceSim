#pragma once

#include <string>

class thruster {
  public:
  virtual void setThrust(double thrust) = 0;
  virtual double getThrust() = 0;
  virtual int getId() = 0;
};
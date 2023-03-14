#pragma once

#include "util.hpp"
#include "radio.hpp"
#include "interfaces.hpp"

#include <map>
#include <queue>
#include <string>
#include <vector>

#include <ode/ode.h>
#include <plugins/physics.h>

#define RECEIVER_CHANNEL 0
#define EMITTER_CHANNEL 1

class physics_radio: public radio {

private:
  satellite* parent;

protected:
  std::string readData() override;
  void sendData(const void* data, int size) override;

  void onPing() override;
  void onThrustSet(thrust_set_body data) override;

public:
  physics_radio(satellite* parent);
};

class physics_object {
protected:
  std::string name;

  dGeomID geom;
  dBodyID body;

  double thrusterForce;

public:
  physics_object(const std::string name);

  dGeomID getGeom();
  dBodyID getBody();
  double getMass();
  double getVelocity(); // TODO
  const double* getPosition();

  void printInfo();

  void setMass(double mass);
  void setForce(double x, double y, double z);
  void setLinearVel(double x, double y, double z);

  void addForce(double x, double y, double z);
};

class physics_thruster : public thruster {
private:
  satellite* parent;
  int id;
  double thrust;

public:
  physics_thruster(satellite* parent, int id);

  double getThrust() override;
  int getId() override;

  void setThrust(double thrust) override;
};

class satellite: public physics_object {
private:
  radio *satelliteRadio;
  std::vector<thruster*> thrusters;

public:
  satellite(const std::string name);
  void tick();

  thruster *getThruster(int id);
};

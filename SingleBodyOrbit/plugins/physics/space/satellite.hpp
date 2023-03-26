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

const static double SHIP_MASS = 420000; // ISS Mass
const static double SHIP_VEL = 7.7;

class physics_radio;
class physics_object;
class physics_thruster;
class satellite;

class physics_radio : public radio {

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
  vec3d getPosition();

  void printInfo();

  void setMass(double mass);
  void setForce(vec3d force);
  void setLinearVelocity(vec3d velocity);

  void addForce(vec3d force);
  void addRelForce(vec3d offset, vec3d force);
};

class physics_thruster : public thruster {
  private:
  satellite* parent;
  int id;
  vec3d offset, direction;
  double thrust;

  public:
  physics_thruster(satellite* parent, int id, vec3d offset, vec3d direction);

  int getId() override;
  double getThrust() override;
  vec3d getForce();
  vec3d getOffset();

  void setThrust(double thrust) override;
};

class satellite : public physics_object {
  private:
  radio* satelliteRadio;
  std::vector<physics_thruster*> thrusters;

  public:
  satellite(const std::string name);
  void init();
  void tick();

  thruster* getThruster(int id);
};

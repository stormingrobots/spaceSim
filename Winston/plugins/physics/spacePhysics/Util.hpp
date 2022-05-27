#pragma once

#include <string>

#include <ode/ode.h>
#include <plugins/physics.h>

double norm(const double* pos);

class PhysicsObject {
  protected:
    std::string name;

    dGeomID geom;
    dBodyID body;

  public:
    PhysicsObject(const std::string name);

    dGeomID getGeom();
    dBodyID getBody();
    double getMass();
    double getVelocity(); //TODO
    const double* getPosition();

    void printInfo();

    void setMass(double mass);
    void setForce(double x, double y, double z);
    void setLinearVel(double x, double y, double z);
};
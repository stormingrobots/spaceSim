#pragma once

#include <ode/ode.h>
#include <plugins/physics.h>

#include "satellite.hpp"
#include "util.hpp"

// Bodies Config
const static double PLANET_MASS = 3e30;

void webots_physics_init();
void webots_physics_step();
void webots_physics_step_end();
int webots_physics_collide(dGeomID g1, dGeomID g2);
void webots_physics_cleanup();
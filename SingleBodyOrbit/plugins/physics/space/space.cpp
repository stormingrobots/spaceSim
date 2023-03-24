#include "space.hpp"

// only if manipulating joints
static pthread_mutex_t mutex;

static physics_object* planet;
static satellite* ship;

void webots_physics_init() {
  pthread_mutex_init(&mutex, NULL);

  planet = new physics_object("Planet");
  ship = new satellite("Satellite");

  planet->setMass(PLANET_MASS);
  ship->init();

  planet->printInfo();
  ship->printInfo();
}

void webots_physics_step() {
  ship->tick();
}

void webots_physics_step_end() {}

int webots_physics_collide(dGeomID g1, dGeomID g2) {
  // Do Nothing Here for now
  return 0;
}

void webots_physics_cleanup() {
  /*
   * Here you need to free any memory you allocated in above, close files, etc.
   * You do not need to free any ODE object, they will be freed by Webots.
   */
  pthread_mutex_destroy(&mutex);
}

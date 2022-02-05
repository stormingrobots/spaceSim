#include "SpacePhysics.hpp"

//only if manipulating joints
static pthread_mutex_t mutex; // needed to run with multi-threaded version of ODE

static PhysicsObject *planet;
static PhysicsObject *ship;

void webots_physics_init() {
  pthread_mutex_init(&mutex, NULL);
  
  planet = new PhysicsObject("Planet");
  ship = new PhysicsObject("Satellite");

  planet->printInfo();
  ship->printInfo();

  planet->setMass(PLANET_MASS);

  ship->setMass(SHIP_MASS);
  ship->setLinearVel(0, 0, SHIP_VEL);
}

void webots_physics_step() {
  double f[3];
  const double *sPos = ship->getPosition();
  // dWebotsConsolePrintf("Ship: %f, %f, %f\n", sPos[0], sPos[1], sPos[2]);

  //at origin
  // const double *pPos = planet->getPosition();
  // dWebotsConsolePrintf("Planet: %f, %f, %f\n", pPos[0], pPos[1], pPos[2]);

  double magnitude = norm(sPos);
  dWebotsConsolePrintf("Magnitude: %f\n", magnitude);

  double fr2 = (MU_EARTH / (magnitude * magnitude * magnitude));

  f[0] = -fr2 * sPos[0];
  f[1] = -fr2 * sPos[1];
  f[2] = -fr2 * sPos[2];

  dWebotsConsolePrintf("Force: %f, %f, %f\n", f[0], f[1], f[2]);
  ship->setForce(f[0], f[1], f[2]);
}

void webots_physics_step_end() {
  
}

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
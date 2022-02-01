/*
 * File:
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

#include <ode/ode.h>
#include <plugins/physics.h>

static pthread_mutex_t mutex; // needed to run with multi-threaded version of ODE
 
static dGeomID planetGeom;
static dBodyID planetBody;

static dGeomID shipGeom;
static dBodyID shipBody;

const static double MU_EARTH = 3.9860442e14;
const static double SHIP_MASS = 420000; //ISS Mass

void webots_physics_init() {
  pthread_mutex_init(&mutex, NULL);
  
  planetGeom = dWebotsGetGeomFromDEF("Planet");
  planetBody = dGeomGetBody(planetGeom);
  dWebotsConsolePrintf("Planet: %p %p \n", planetGeom, planetBody);
  
  shipGeom = dWebotsGetGeomFromDEF("Satellite");
  shipBody = dGeomGetBody(shipGeom);
  dWebotsConsolePrintf("Ship: %p %p \n", shipGeom, shipBody);
  dMass mass; dBodyGetMass(shipBody, &mass); mass.mass = SHIP_MASS;
  dBodySetMass(shipBody, &mass);
  dBodySetLinearVel(shipBody, 0, 0, 7.7f); //7.7 km/s
  
  //Use this model whenever manipulating physics
  // pthread_mutex_lock(&mutex);
  //Stuff here
  // pthread_mutex_unlock(&mutex);
}

double norm(const dReal* pos) {
  return sqrt(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]);
}

void webots_physics_step() {
  double f[3];
  const dReal *r;
  double rMag, fr2;
  r = dBodyGetPosition(shipBody);
  rMag = norm(r);
  fr2 = (MU_EARTH / (rMag * rMag * rMag));
  
  f[0] = fr2 * r[0];
  f[1] = fr2 * r[1];
  f[2] = fr2 * r[2];
  
  dBodyAddForce(shipBody, f[0], f[1], f[2]);
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

#include "space.hpp"

// only if manipulating joints
static pthread_mutex_t mutex;

static physics_object planet;
static satellite ship;

static std::vector<physics_object*> objects;

void webots_physics_init() {
  pthread_mutex_init(&mutex, NULL);

  planet.init("Planet");
  planet.setMass(PLANET_MASS);

  ship.init("Satellite");
  ship.setMass(SHIP_MASS);
  ship.setLinearVelocity({ 0, 0, SHIP_VEL });
  objects.push_back(&ship);
}

void webots_physics_step() {
  //gravity
  for(auto& object: objects) {
    object->setForce(vec3d());
    planet.applyGravity(*object);
  }

  ship.tick();
}

void webots_physics_step_end() {}

int webots_physics_collide(dGeomID g1, dGeomID g2) {
  // Do Nothing Here for now
  return 0;
}

void webots_physics_cleanup() {

  pthread_mutex_destroy(&mutex);
}

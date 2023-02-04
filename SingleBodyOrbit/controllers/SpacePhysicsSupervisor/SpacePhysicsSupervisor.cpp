#include <webots/Node.hpp>
#include <webots/Supervisor.hpp>

#include <string>

#define MAX_COORDS 20000

using namespace webots;

static void create_trail_shape(Supervisor* supervisor) {
  Node* trail = supervisor->getFromDef("TRAIL");
  if(trail) trail->remove();
  
  std::string trailString;
  
  trailString +=
    "DEF TRAIL Shape {\n"
    "  appearance Appearance {\n"
    "    material Material {\n"
    "      diffuseColor 0 1 0\n"
    "      emissiveColor 0 1 0\n"
    "    }\n"
    "  }\n"
    "  geometry DEF TRAIL_LINE_SET IndexedLineSet {\n"
    "    coord Coordinate {\n"
    "      point [\n";
    
  for(int i = 0; i < MAX_COORDS; ++i) trailString += "      0 0 0\n";
  trailString +=
    "      ]\n"
    "    }\n"
    "    coordIndex[\n";
  for(int i = 0; i < MAX_COORDS; ++i) trailString += "      0 0 -1\n";
  trailString +=
    "    ]\n"
    "  }\n"
    "}\n";
  
  Field* field = supervisor->getRoot()->getField("children");
  field->importMFNodeFromString(-1, trailString);
}

int main(int argc, char **argv) {
  // create the Robot instance.
  Robot* robot = new Robot();
  Supervisor* supervisor = (Supervisor*) robot;

  // get the time step of the current world.
  int timeStep = (int)supervisor->getBasicTimeStep();

  create_trail_shape(supervisor);
  
  Node* root = supervisor->getRoot();
  Node* target = supervisor->getFromDef("Satellite");
  
  Node* trailLineSet = supervisor->getFromDef("TRAIL_LINE_SET");
  Node* coord = trailLineSet->getField("coord")->getSFNode();
  Field* point = coord->getField("point");
  Field* coordIndex = trailLineSet->getField("coordIndex");
  
  int index = 0;
  bool firstStep = true;
  
  while (supervisor->step(timeStep) != -1) {
    const double* targetTrans = target->getPosition();
    point->setMFVec3f(index, targetTrans);
    
    if(index > 0) {
      coordIndex->setMFInt32(3 * (index - 1), index - 1);
      coordIndex->setMFInt32(3 * (index - 1) + 1, index);
    } else if(index == 0 && firstStep == false) {
      coordIndex->setMFInt32(3 * (MAX_COORDS - 1), 0);
      coordIndex->setMFInt32(3 * (MAX_COORDS - 1) + 1, MAX_COORDS - 1);
    }
    
    coordIndex->setMFInt32(3 * index, index);
    coordIndex->setMFInt32(3 * index + 1, index);
    
    firstStep = false;
    index++;
    index = index % MAX_COORDS;
  };

  // Enter here exit cleanup code.

  delete supervisor;
  return 0;
}

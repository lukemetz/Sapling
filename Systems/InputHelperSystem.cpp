#include "InputHelperSystem.h"
#include <GL/glfw.h>
#include "../App.h"

using namespace Component;

void InputHelperSystem::run(float dt)
{
  std::vector<Entity *> entities;
  ensys->getEntities<Input>(entities);
  if(entities.size() > 0)
  {
    if (entities[0]->getAs<Input>()->keys[GLFW_KEY_ESC] == true) {
      Application::sharedInstance()->close();
    }
  }
}

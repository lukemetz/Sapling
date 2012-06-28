#include "InputHelperSystem.h"
#include <GL/glfw.h>
#include "../App.h"

void InputHelperSystem::run(float dt)
{
  std::vector<Entity *> entities;
  ensys->getEntities<InputComponent>(entities);
  if(entities.size() > 0)
  {
    if (entities[0]->getAs<InputComponent>()->keys[GLFW_KEY_ESC] == true) {
      Application::sharedInstance()->close();
    }
  }
}

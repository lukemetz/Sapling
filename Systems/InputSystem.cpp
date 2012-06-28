#include "InputSystem.h"
#include <GL/glfw.h>

InputSystem::InputSystem(EntitySystem *en)
{
  ensys = en;

  glfwEnable( GLFW_STICKY_KEYS );
}

void InputSystem::run(float dt)
{
	for( int i = 0; i < 320; ++i ) {
    prevKeys[i] = keys[i];
		keys[i] = (glfwGetKey( i ) == GLFW_PRESS);
  }
  glfwGetMousePos(&mouseX, &mouseY);

  std::vector<Entity*> entities;
	ensys->getEntities<InputComponent>(entities);
  InputComponent *ic;
	for(std::vector<Entity*>::iterator it = entities.begin(); it!=entities.end(); ++it) {
		ic = (*it)->getAs<InputComponent>();
    ic->keys = keys;
		ic->prevKeys = prevKeys;
		ic->prevMouseX = ic->mouseX;
		ic->prevMouseY = ic->mouseY;
		ic->mouseX = mouseX;
		ic->mouseY = mouseY;
	}
}

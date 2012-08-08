#include "InputSystem.h"
#include <GL/glfw.h>

using namespace Component;

InputSystem::InputSystem()
{
  ensys = EntitySystem::sharedInstance();

  glfwEnable( GLFW_STICKY_KEYS );
}

void InputSystem::run(float dt)
{
	for( int i = 0; i < 320; ++i ) {
    prevKeys[i] = keys[i];
		keys[i] = (glfwGetKey( i ) == GLFW_PRESS);
  }

  for( int i = 0; i < 8; ++i) {
    prevMouseButtons[i] = mouseButtons[i];
    mouseButtons[i] = (glfwGetMouseButton(GLFW_MOUSE_BUTTON_1
          +i) != GLFW_RELEASE);
  }

  glfwGetMousePos(&mouseX, &mouseY);

  std::vector<Entity*> entities;
	ensys->getEntities<Input>(entities);
  Input *ic;
	for(Entity * entity : entities) {
		ic = entity->getAs<Input>();
    ic->keys = keys;
		ic->prevKeys = prevKeys;
    ic->mouseButtons = mouseButtons;
    ic->prevMouseButtons = prevMouseButtons;
		ic->prevMouseX = ic->mouseX;
		ic->prevMouseY = ic->mouseY;
		ic->mouseX = mouseX;
		ic->mouseY = mouseY;
	}
}

#include "MovementSelectorSystem.h"

#include "Components/MovementComponent.h"
#include "Components/AnimationTimerComponent.h"
#include "Components/TileSelectedComponent.h"
#include <Components/components.h>
#include <App.h>
#include "Utils.h"

MovementSelectorSystem::MovementSelectorSystem()
{
  ensys = EntitySystem::sharedInstance();
}

void MovementSelectorSystem::run(float dt)
{
  std::vector<Entity*> entities;
  ensys->getEntities<MovementComponent>(entities);
  std::vector<Entity*>::iterator it;
  Application *app = Application::sharedInstance();

  std::vector<Entity*> cameraEntities;
  ensys->getEntities<CameraComponent>(cameraEntities);

  Entity* cameraEntity = cameraEntities[0];

  for(Entity *entity : entities) {
    MovementComponent *mc = entity->getAs<MovementComponent>();
    TransformComponent *tc = entity->getAs<TransformComponent>();
    InputComponent *ic = entity->getAs<InputComponent>();

    if (mc != nullptr && ic != nullptr && tc != nullptr) {
      if (ic->mouseButtons[0] == true && ic->prevMouseButtons[0] == false)
      {
        float normalizedMouseX = ic->mouseX/app->appWidth;

        float normalizedMouseY = (app->appHeight - ic->mouseY)/app->appHeight;
        float ox, oy, oz, dx, dy, dz;

        H3DNode node = h3dutPickNode(cameraEntity->getAs<CameraComponent>()->node, normalizedMouseX, normalizedMouseY);
        Entity * en = Utils::sharedInstance()->getEntityForNode(node);
        if (en != nullptr) {
          TileSelectedComponent *tc = en->getAs<TileSelectedComponent>();
          if (tc != nullptr) {
            tc->selected = 1;

          }
        }
      }
    }
  }
}

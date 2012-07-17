#include "PlayerControlSystem.h"
#include "Components/SelectedEntityComponent.h"
#include "Components/TileObjectComponent.h"
#include <GL/glfw.h>
#include "App.h"
#include "Utils.h"


void PlayerControlSystem::run(float dt)
{
  std::vector<Entity *> entities;
  EntitySystem *ensys = EntitySystem::sharedInstance();
  ensys->getEntities<PlayerStateComponent>(entities);

  for (Entity *entity : entities) {
    mouseSelectObject(entity);
    keyboardDeselect(entity);
  }
}

void PlayerControlSystem::mouseSelectObject(Entity *entity)
{
  EntitySystem *ensys = EntitySystem::sharedInstance();
  std::vector<Entity*> cameraEntities;
  ensys->getEntities<CameraComponent>(cameraEntities);
  Entity* cameraEntity = cameraEntities[0];

  InputComponent *ic = entity->getAs<InputComponent>();
  if (ic->mouseButtons[0] == true && ic->prevMouseButtons[0] == false) {
    PlayerStateComponent *playerStateComponent = entity->getAs<PlayerStateComponent>();

    Application *app = Application::sharedInstance();
    float normalizedMouseX = ic->mouseX/app->appWidth;
    float normalizedMouseY = (app->appHeight - ic->mouseY)/app->appHeight;
    H3DNode node = h3dutPickNode(cameraEntity->getAs<CameraComponent>()->node, normalizedMouseX, normalizedMouseY);
    Entity *pickSelectedEntity = Utils::sharedInstance()->getEntityForNode(node);

    auto tileObjectComponent = pickSelectedEntity->getAs<TileObjectComponent>();
    if (nullptr != tileObjectComponent) {
      entity->getAs<SelectedEntityComponent>()->entity = pickSelectedEntity;
      playerStateComponent->state = kPlayerSelected;
      printf("Tile object selected \n");
    }
  }
}

void PlayerControlSystem::keyboardDeselect(Entity *entity)
{
  InputComponent *ic = entity->getAs<InputComponent>();
  if ( ic->keys['C'] && !ic->prevKeys['C'] ) {
    auto selectedEntityComponent = entity->getAs<SelectedEntityComponent>();
    selectedEntityComponent->entity = nullptr;
    auto playerStateComponent = entity->getAs<PlayerStateComponent>();
    playerStateComponent->state = kPlayerDeselected;
    printf("Deselected tile object\n");
  }
}

#include "PlayerControlSystem.h"
#include "Components/SelectedEntityComponent.h"
#include "Components/TileObjectComponent.h"
#include "Components/UnitSelectedComponent.h"
#include <GL/glfw.h>
#include "App.h"
#include "Utils.h"
#include "Helper.h"

void PlayerControlSystem::preRun(float dt)
{
  std::vector<Entity *> entities;
  EntitySystem *ensys = EntitySystem::sharedInstance();
  ensys->getEntities<PlayerStateComponent>(entities);
  for (Entity *entity : entities) {
    mouseSelectObject(entity);
    keyboardDeselect(entity);

    auto ic = entity->getAs<InputComponent>();
    auto psc = entity->getAs<PlayerStateComponent>();
    if (ic->keys['P'] && !ic->prevKeys['P']) {
      psc->state = kPlayerAnimating;
    }
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

    Application *app = Application::sharedInstance();
    float normalizedMouseX = ic->mouseX/app->appWidth;
    float normalizedMouseY = (app->appHeight - ic->mouseY)/app->appHeight;
    H3DNode node = h3dutPickNode(cameraEntity->getAs<CameraComponent>()->node, normalizedMouseX, normalizedMouseY);
    Entity *pickSelectedEntity = Utils::sharedInstance()->getEntityForNode(node);
    if (nullptr != pickSelectedEntity) {
      auto tileObjectComponent = pickSelectedEntity->getAs<TileObjectComponent>();
      if (nullptr != tileObjectComponent) {
        selectUnit(entity, pickSelectedEntity);
        printf("Tile object selected \n");
      }
    }
  }
}

void PlayerControlSystem::keyboardDeselect(Entity *entity)
{
  InputComponent *ic = entity->getAs<InputComponent>();
  if ( ic->keys['C'] && !ic->prevKeys['C'] ) {
    deselectUnit(entity);
    printf("Deselected tile object\n");
  }
}

void PlayerControlSystem::selectUnit(Entity *current, Entity *selected)
{
  auto unitSelectedComponent = selected->getAs<UnitSelectedComponent>();
  unitSelectedComponent->selected = true;
  current->getAs<SelectedEntityComponent>()->entity = selected;
  current->getAs<PlayerStateComponent>()->state = kPlayerSelected;
}

void PlayerControlSystem::deselectUnit(Entity *current)
{
  auto selectedEntityComponent = current->getAs<SelectedEntityComponent>();
  Entity *selectedEntity = selectedEntityComponent->entity;
  if (nullptr == selectedEntity) {
    return;
  }

  auto unitSelected = selectedEntity->getAs<UnitSelectedComponent>();
  if (unitSelected != nullptr) {
    unitSelected->selected = false;
    unitSelected->usingAbility = false;
    selectedEntityComponent->entity = nullptr;
  }
  auto playerStateComponent = current->getAs<PlayerStateComponent>();
  playerStateComponent->state = kPlayerDeselected;

  Helper::deselectAllTiles();
}

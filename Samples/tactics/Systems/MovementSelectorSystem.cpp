#include "MovementSelectorSystem.h"

#include "Components/MovementComponent.h"
#include "Components/AnimationTimerComponent.h"
#include "Components/TileSelectedComponent.h"
#include "Components/TileComponent.h"
#include "Components/TileObjectComponent.h"
#include "Components/SelectedEntityComponent.h"
#include "Components/UnitSelectedComponent.h"
#include <Components/components.h>
#include <App.h>
#include "Utils.h"

MovementSelectorSystem::MovementSelectorSystem()
{
  ensys = EntitySystem::sharedInstance();
}

void MovementSelectorSystem::run(float dt)
{
  Application *app = Application::sharedInstance();

  std::vector<Entity*> cameraEntities;
  ensys->getEntities<CameraComponent>(cameraEntities);
  Entity* cameraEntity = cameraEntities[0];

  std::vector<Entity*> entities;
  ensys->getEntities<MovementComponent>(entities);
  for(Entity *entity : entities) {
    if ( !unitCanMove(entity) ) {
      continue;
    }

    MovementComponent *mc = entity->getAs<MovementComponent>();
    TransformComponent *tc = entity->getAs<TransformComponent>();
    InputComponent *ic = entity->getAs<InputComponent>();

    selectPossibleLocations(entity);

    if (ic->mouseButtons[0] == true && ic->prevMouseButtons[0] == false) {
      float normalizedMouseX = ic->mouseX/app->appWidth;

      float normalizedMouseY = (app->appHeight - ic->mouseY)/app->appHeight;

      H3DNode node = h3dutPickNode(cameraEntity->getAs<CameraComponent>()->node, normalizedMouseX, normalizedMouseY);
      Entity * en = Utils::sharedInstance()->getEntityForNode(node);
      if (en != nullptr) {
        TileSelectedComponent *tc = en->getAs<TileSelectedComponent>();
        SelectedEntityComponent *sc = entity->getAs<SelectedEntityComponent>();
        if (tc != nullptr) {
          tc->selected = 1;
          if (sc != nullptr) {
            Entity *oldEntity = sc->entity;
            if (oldEntity != nullptr) {
              TileSelectedComponent *oldTc = oldEntity->getAs<TileSelectedComponent>();
              if (oldTc != nullptr) {
                oldTc->selected = 0;
              }
            }
            sc->entity = en;
          }
        }
      }
    }
  }
}

bool MovementSelectorSystem::unitCanMove(Entity *entity)
{
  auto unitSelected = entity->getAs<UnitSelectedComponent>();
  return unitSelected->selected && !unitSelected->usingAbility;
}

std::map<Entity *, MovementPath> MovementSelectorSystem::getMovementLocationsAndPaths(Entity *entity)
{
  std::map<Entity *, MovementPath> locationToPath;
  Entity *currentTile = entity->getAs<TileObjectComponent>()->tile;
  std::vector<Entity *>neighbors = currentTile->getAs<TileComponent>()->neighbors;

  for (Entity *tile : neighbors)
  {
    MovementPath movePath;
    movePath.time = 1.0f;
    movePath.path.push_back(currentTile);
    movePath.path.push_back(tile);
    locationToPath[tile] = movePath;
  }
  return locationToPath;
}

void MovementSelectorSystem::selectPossibleLocations(Entity *entity)
{
  std::map<Entity *, MovementPath> paths = getMovementLocationsAndPaths(entity);
  auto iter = paths.begin();
  for (; iter != paths.end(); ++iter) {
    Entity *finalLocation = iter->first;
    finalLocation->getAs<TileSelectedComponent>()->selected = true;
  }
}


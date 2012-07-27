#include "MovementSelectorSystem.h"

#include "Helper.h"
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
  Entity* cameraEntity = Helper::getCamera();
  std::vector<Entity*> entities = ensys->getEntities<MovementComponent>();
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

std::map<Entity *, MovementPath>
  MovementSelectorSystem::getMovementLocationsAndPaths(Entity *entity, Entity *onTile, MovementPath move)
{
  std::map<Entity *, MovementPath> locationToPath;
  std::vector<Entity *> neighbors = onTile->getAs<TileComponent>()->neighbors;
  move.time += 1;
  move.path.push_back(onTile);
  locationToPath[onTile] = move;
  if(move.time < 3) {
    for (Entity *tile : neighbors)
    {
      if (nullptr != tile) {
        auto movementLocationPaths = getMovementLocationsAndPaths(entity, tile, move);
        locationToPath = mergeEntityMovementPathMap(locationToPath, movementLocationPaths);
      }
    }
  }
  return locationToPath;
}

std::map<Entity *, MovementPath>
  MovementSelectorSystem::mergeEntityMovementPathMap(std::map<Entity *, MovementPath> path1, std::map<Entity *, MovementPath> path2)
{
  auto mapIter = path2.begin();
  for (; mapIter != path2.end(); ++mapIter) {
    Entity *tile = mapIter->first;
    MovementPath movePath = mapIter->second;
    if (path1.count(tile) == 0 || path1[tile].time > movePath.time) {
      path1[tile] = movePath;
    }
  }
  return path1;
}

void MovementSelectorSystem::selectPossibleLocations(Entity *entity)
{
  Entity * onTile = entity->getAs<TileObjectComponent>()->tile;
  MovementPath noMove;
  noMove.time = 0;

  std::map<Entity *, MovementPath> paths = getMovementLocationsAndPaths(entity, onTile, noMove);
  auto iter = paths.begin();
  for (; iter != paths.end(); ++iter) {
    Entity *finalLocation = iter->first;
    finalLocation->getAs<TileSelectedComponent>()->selected = true;
  }
}


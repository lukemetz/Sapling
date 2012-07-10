#include <jansson.h>
#include "Systems.h"
#include "Wrappers/WrapManager.h"
#include "App.h"

#include "Components/TileComponent.h"
#include "Components/TileObjectComponent.h"
#include "Components/UnitComponent.h"
#include "Components/AnimationTimerComponent.h"
#include "Components/MovementComponent.h"
#include "Systems/MovementSystem.h"
#include "Systems/AnimationTimerSystem.h"

#include <stdlib.h>

static bool running;
static double t0;
static Application *app;

void engineInit() {
	EntitySystem *entitySystem = Application::sharedInstance()->entitySystem;

  WrapManager *wrapManager = new WrapManager();
  json_error_t error;
  json_t *entity = json_load_file("entities.json", 0, &error);
  if (entity == NULL) {
    printf("Error: %s, %d", error.text, error.line);
  }
  const char *key;
  json_t *value;
  json_object_foreach(entity, key, value) {
    printf("%s Entity found \n", key);
    wrapManager->loadEntity(entitySystem, value);
  }

  int size = 10;

  std::vector<std::vector<Entity *> > entities;
  for(int i=0; i < size; i++) {
    entities.push_back(std::vector<Entity *>());
    for(int j=0; j < size; j++) {
      Entity *tile = new Entity;
      entities[i].push_back(tile);
      entitySystem->createComponent<MeshComponent>(tile);
      entitySystem->createComponent<TransformComponent>(tile);
      entitySystem->createComponent<TileComponent>(tile);
      tile->getAs<MeshComponent>()->path = "models/tile.scene.xml";
      tile->getAs<TransformComponent>()->pos = Vec3f(i, (float)rand()/RAND_MAX/4.0f, j);
    }
  }

  for(int i=0; i < size; i++) {
    for(int j=0; j < size; j++){
      TileComponent *tc = entities[i][j]->getAs<TileComponent>();
      if(j>1) {
        tc->neighbors.push_back(entities[i][j-1]);
      } else {
        tc->neighbors.push_back(NULL);
      }
      if(i>1) {
        tc->neighbors.push_back(entities[i-1][j]);
      } else {
        tc->neighbors.push_back(NULL);
      }
      if(j<size-1) {
        tc->neighbors.push_back(entities[i][j+1]);
      } else {
        tc->neighbors.push_back(NULL);
      }
      if(i<size-1) {
        tc->neighbors.push_back(entities[i+1][j]);
      } else {
        tc->neighbors.push_back(NULL);
      }
    }
  }

  //Throw a dude on the feild

  Entity *en = new Entity;
  entitySystem->createComponent<TileObjectComponent>(en);
  entitySystem->createComponent<UnitComponent>(en);
  entitySystem->createComponent<TransformComponent>(en);
  entitySystem->createComponent<MeshComponent>(en);
  entitySystem->createComponent<MovementComponent>(en);
  entitySystem->createComponent<AnimationTimerComponent>(en);
  entitySystem->createComponent<MovementComponent>(en);

  en->getAs<MeshComponent>()->path = "models/unit.scene.xml";
  en->getAs<TileObjectComponent>()->tile = entities[5][5];
  en->getAs<TransformComponent>()->pos = Vec3f(5,2,5);

  en->getAs<MovementComponent>()->tiles.push_back(entities[5][6]);
  en->getAs<MovementComponent>()->tiles.push_back(entities[5][7]);
  en->getAs<MovementComponent>()->tiles.push_back(entities[4][7]);
  en->getAs<MovementComponent>()->tiles.push_back(entities[3][7]);
  en->getAs<MovementComponent>()->tiles.push_back(entities[3][6]);
  en->getAs<MovementComponent>()->tiles.push_back(entities[3][5]);

  entitySystem->addSystem<RenderSystem>();
  entitySystem->addSystem<InputSystem>();
  entitySystem->addSystem<InputMoverSystem>();
  entitySystem->addSystem<InputHelperSystem>();
  entitySystem->addSystem<WobbleMoverSystem>();
  entitySystem->addSystem<MovementSystem>();
  entitySystem->addSystem<AnimationTimerSystem>();
}

int main( int argc, char** argv )
{
	app = new Application( Application::extractAppPath( argv[0] ) );
  //glfwDisable( GLFW_MOUSE_CURSOR );
  engineInit();

  app->resize(1024, 576);

	t0 = glfwGetTime();
	app->running = true;
	while( app->running )
	{
		double t = glfwGetTime();
    double dt = t-t0;
    t0 = t;
		if( dt > 1 ) dt = 1.0f/30.0f;  // Handle breakpoints
		app->mainLoop( dt );
	}
	app->release();
	delete app;
  return 0;
}

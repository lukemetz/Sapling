#include <jansson.h>
#include "Systems.h"
#include "Wrappers/WrapManager.h"
#include "App.h"
#include "Components/components.h"
static double t0;
static Application *app;
void engineInit() {
	EntitySystem *entitySystem = EntitySystem::sharedInstance();

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

  //entitySystem->getEntities<Component::Camera>()[0]->getAs<Component::Camera>()->debug = true;
  auto entities = entitySystem->getEntities<Component::Camera>();
  if (entities.size() == 0) {
    printf("ERROR: Please run this in the same directory that the binary is in. \n");
  }
  entities[0]->getAs<Component::Camera>()->debug = true;
  entitySystem->addSystem<RenderSystem>();
  entitySystem->addSystem<InputSystem>();
  entitySystem->addSystem<InputMoverSystem>();
  entitySystem->addSystem<InputHelperSystem>();
  entitySystem->addSystem<WobbleMoverSystem>();
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
		t0 = t;
    double dt = t0-t;
    t0 = t;
		if( dt > 1 ) dt = 1.0f/30.0f;  // Handle breakpoints
		app->mainLoop( dt );
	}
	app->release();
	delete app;
  return 0;
}

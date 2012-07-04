#include "App.h"
#include <horde3d/Horde3D.h>
#include <horde3d/Horde3DUtils.h>
#include <math.h>
#include <iomanip>

#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/InputMoverSystem.h"
#include "Systems/InputHelperSystem.h"
#include "Systems/WobbleMoverSystem.h"
#include "Wrappers/WrapManager.h"
#include <jansson.h>

using namespace std;

std::string Application::appPath = "";
Application *Application::instance = NULL;

Application::Application( const std::string &_appPath )
{
	_curFPS = 30;
	_statMode = 0;
	_freezeMode = 0; _debugViewMode = false; _wireframeMode = false;
	_cam = 0;
	Application::appPath = _appPath;

  running = true;
  Application::instance = this;


  appWidth = 1024;
  appHeight = 576;
  fullScreen = false;


	glfwInit();
	if(!setupWindow(appWidth, appHeight, fullScreen)){
    printf("Error setting up window\n");
    return;
  }

	if( !fullScreen ) {
    glfwSetWindowTitle(getTitle());
  }

	if ( !init() )
	{
		glfwCloseWindow();
		glfwOpenWindow( 800, 16, 8, 8, 8, 8, 24, 8, GLFW_WINDOW );
		glfwSetWindowTitle( "Unable to initalize engine - Make sure you have an OpenGL 2.0 compatible graphics card" );
		double startTime = glfwGetTime();
		while( glfwGetTime() - startTime < 5.0 ) {}  // Sleep

    std::cout << "Unable to initalize engine" << std::endl;
		std::cout << "Make sure you have an OpenGL 2.0 compatible graphics card";
		glfwTerminate();
		return;
	}
	resize( appWidth, appHeight );

}

Application *Application::sharedInstance()
{
  return Application::instance;
}

void Application::close()
{
  running = false;
}

bool Application::init()
{
	// Initialize engine
	if( !h3dInit() )
	{
		h3dutDumpMessages();
		return false;
	}

	// Set options
	h3dSetOption( H3DOptions::LoadTextures, 1 );
	h3dSetOption( H3DOptions::TexCompression, 0 );
	h3dSetOption( H3DOptions::FastAnimation, 0 );
	h3dSetOption( H3DOptions::MaxAnisotropy, 4 );
	h3dSetOption( H3DOptions::ShadowMapSize, 2048 );

	// Add resources
	// Pipelines
	_hdrPipeRes = h3dAddResource( H3DResTypes::Pipeline, "pipelines/hdr.pipeline.xml", 0 );
	_forwardPipeRes = h3dAddResource( H3DResTypes::Pipeline, "pipelines/forward.pipeline.xml", 0 );
	// Overlays
	_fontMatRes = h3dAddResource( H3DResTypes::Material, "overlays/font.material.xml", 0 );
	_panelMatRes = h3dAddResource( H3DResTypes::Material, "overlays/panel.material.xml", 0 );
	_logoMatRes = h3dAddResource( H3DResTypes::Material, "overlays/logo.material.xml", 0 );

	// Load resources
	h3dutLoadResourcesFromDisk((Application::appPath+"Content").c_str());


	H3DNode matRes = h3dFindResource( H3DResTypes::Material, "pipelines/postHDR.material.xml" );
	h3dSetMaterialUniform( matRes, "hdrExposure", 2.5f, 0, 0, 0 );
	h3dSetMaterialUniform( matRes, "hdrBrightThres", 0.5f, 0, 0, 0 );
	h3dSetMaterialUniform( matRes, "hdrBrightOffset", 0.08f, 0, 0, 0 );

	engineInit();
	return true;
}

void Application::engineInit() {
	entitySystem = new EntitySystem();
  WrapManager *wrapManager = new WrapManager();
  json_error_t error;
  json_t *entity = json_load_file("entities.json", 0, &error);
  const char *key;
  json_t *value;
  json_object_foreach(entity, key, value) {
    printf("%s Entity found \n", key);
    wrapManager->loadEntity(entitySystem, value);
  }

  entitySystem->addSystem<RenderSystem>();
  entitySystem->addSystem<InputSystem>();
  entitySystem->addSystem<InputMoverSystem>();
  entitySystem->addSystem<InputHelperSystem>();
  entitySystem->addSystem<WobbleMoverSystem>();
}

void Application::mainLoop( float dt )
{
  entitySystem->update(dt);


  glfwSwapBuffers();
}

void Application::release()
{
	h3dRelease();
	glfwEnable( GLFW_MOUSE_CURSOR );
	glfwTerminate();
}

void Application::resize( int width, int height )
{
	std::vector<Entity*> entities;
	entitySystem->getEntities<CameraComponent>(entities);
	CameraComponent* cc = entities[0]->getAs<CameraComponent>(); //Todo add a check here.

	// Resize viewport
	h3dSetNodeParamI( cc->node, H3DCamera::ViewportXI, 0 );
	h3dSetNodeParamI( cc->node, H3DCamera::ViewportYI, 0 );
	h3dSetNodeParamI( cc->node, H3DCamera::ViewportWidthI, width );
	h3dSetNodeParamI( cc->node, H3DCamera::ViewportHeightI, height );

	// Set virtual camera parameters
	h3dSetupCameraView( cc->node, 45.0f, (float)width / height, 0.1f, 1000.0f );
	h3dResizePipelineBuffers( cc->pipeline, width, height );
}

int windowCloseListener()
{
  Application::sharedInstance()->running = false;
	return 0;
}

bool Application::setupWindow( int width, int height, bool fullscreen )
{
	if( !glfwOpenWindow( width, height, 8, 8, 8, 8, 24, 8, fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW ) )
	{
		glfwTerminate();
		return false;
	}
	glfwSwapInterval( 0 );
	glfwSetWindowCloseCallback( windowCloseListener );
	return true;
}

std::string Application::extractAppPath( char *fullPath )
{
#ifdef __APPLE__
	std::string s( fullPath );
	for( int i = 0; i < 4; ++i )
		s = s.substr( 0, s.rfind( "/" ) );
	return s + "/../";
#else
	const std::string s( fullPath );
	if( s.find( "/" ) != std::string::npos )
		return s.substr( 0, s.rfind( "/" ) ) + "/";
	else if( s.find( "\\" ) != std::string::npos )
		return s.substr( 0, s.rfind( "\\" ) ) + "\\";
	else
		return "";
#endif
}

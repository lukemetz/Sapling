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
	Entity *e1 = new Entity;
	TransformComponent *tc;
  CameraComponent *cc;
  InputComponent *ic;
  LightComponent *lc;
  WobbleMoverComponent *wc;

  tc = entitySystem->createComponent<TransformComponent>(e1);
	cc = entitySystem->createComponent<CameraComponent>(e1);
	ic = entitySystem->createComponent<InputComponent>(e1);
  lc = entitySystem->createComponent<LightComponent>(e1);
  lc->color[1] = 0;

	entitySystem->createComponent<InputMoverComponent>(e1);

	Entity *e2 = new Entity;
	tc = entitySystem->createComponent<TransformComponent>(e2);
	MeshComponent *mc = entitySystem->createComponent<MeshComponent>(e2);
  mc->path = "models/knight/knight.scene.xml";
  tc->pos.y = 0;

  Entity *e3 = new Entity;
  tc = entitySystem->createComponent<TransformComponent>(e3);
  lc = entitySystem->createComponent<LightComponent>(e3);
  wc = entitySystem->createComponent<WobbleMoverComponent>(e3);

  entitySystem->addSystem<RenderSystem>();
  entitySystem->addSystem<InputSystem>();
  entitySystem->addSystem<InputMoverSystem>();
  entitySystem->addSystem<InputHelperSystem>();
  entitySystem->addSystem<WobbleMoverSystem>();
}

void Application::mainLoop( float fps )
{
	_curFPS = fps;
  float dt = 1/fps;

  entitySystem->update(dt);
}

void Application::release()
{
	h3dRelease();
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

#pragma once

#include <horde3d/Horde3D.h>
#include <sstream>
#include <string>
#include <GL/glfw.h>
#include <iostream>

#include "Components/components.h"
#include "Components/userComponents.h"
#include "EntitySystem.h"

class Application
{
public:
	Application( const std::string &_appPath );

	const char *getTitle() { return "Knight - Horde3D Sample"; }

	bool init();
	void mainLoop( float dt );
	void release();
	void resize( int width, int height );
  void close();

	void engineInit();

  static Application *sharedInstance();

  static std::string appPath;

  bool running;

  static bool setupWindow(int width, int height, bool fullscreen);
  static std::string extractAppPath(char *fullPath);

private:

  int appWidth;
  int appHeight;
  bool fullScreen;

	float              _curFPS;
	std::stringstream  _text;

	int                _statMode;
	int                _freezeMode;
	bool               _debugViewMode, _wireframeMode;

	// Engine objects
	H3DRes             _fontMatRes, _panelMatRes;
	H3DRes             _pipeRes, _logoMatRes, _hdrPipeRes, _forwardPipeRes;
	H3DNode            _cam;

	EntitySystem *entitySystem;

  static Application *instance;
};

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <GL/glfw.h>
#include "App.h"

// Configuration
const int appWidth = 1024;
const int appHeight = 576;
static bool fullScreen = false;
static int benchmarkLength = 600;

bool setupWindow( int, int, bool );
static bool running;
static double t0;
static int mx0, my0;
static Application *app;


std::string extractAppPath( char *fullPath )
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


int windowCloseListener()
{
	app->running = false;
	return 0;
}

bool setupWindow( int width, int height, bool fullscreen )
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


int main( int argc, char** argv )
{
	glfwInit();
	if( !setupWindow( appWidth, appHeight, fullScreen ) ) return -1;

	app = new Application( extractAppPath( argv[0] ) );
	if( !fullScreen ) glfwSetWindowTitle( app->getTitle() );

	if ( !app->init() )
	{
		glfwCloseWindow();
		glfwOpenWindow( 800, 16, 8, 8, 8, 8, 24, 8, GLFW_WINDOW );
		glfwSetWindowTitle( "Unable to initalize engine - Make sure you have an OpenGL 2.0 compatible graphics card" );
		double startTime = glfwGetTime();
		while( glfwGetTime() - startTime < 5.0 ) {}  // Sleep

		std::cout << "Unable to initalize engine" << std::endl;
		std::cout << "Make sure you have an OpenGL 2.0 compatible graphics card";
		glfwTerminate();
		return -1;
	}
	app->resize( appWidth, appHeight );

	//glfwDisable( GLFW_MOUSE_CURSOR );

	int frames = 0;
	float fps = 30.0f;
	t0 = glfwGetTime();
	app->running = true;

	// Game loop
	while( app->running )
	{
		// Calc FPS
		++frames;
		if( frames >= 3 )
		{
			double t = glfwGetTime();
			fps = frames / (float)(t - t0);
			if( fps < 5 ) fps = 30;  // Handle breakpoints
			frames = 0;
			t0 = t;
		}

		// Render
		app->mainLoop( fps );
		glfwSwapBuffers();
	}

	glfwEnable( GLFW_MOUSE_CURSOR );

	app->release();
	delete app;
	glfwTerminate();

  return 0;
}

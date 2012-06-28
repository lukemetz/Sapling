Sapling
=======

Sapling is a highly experimental entity-system based game engine.
It was inspired by the series of [blog post by T=Machine](http://t-machine.org/index.php/2007/09/03/entity-systems-are-the-future-of-mmog-development-part-1/).


##Dependencies

Sapling is currently built with premake4.

It uses Horde3D for graphics. Many of the default assets and graphics pipelines are also from horde. The c++ math helper file, utMath.h, also comes from horde3d with slight modifications.

GLFW is used for input as well as creating a openGL window.

##Building
Sapling should be cross platform, but it has only been tested on Linux.

To build simply run premake4 gmake. Then make in the main directory.

Currently a sample test application is built instead of a library. This will change soon.

##License

All source is provided with absolutely no warranty and is under a [EPL](http://www.eclipse.org/legal/epl-v10.html) for now.

Sapling
=======

Sapling is a highly experimental entity-system based game engine written in c++11.
It was inspired by the series of [blog post by T=Machine](http://t-machine.org/index.php/2007/09/03/entity-systems-are-the-future-of-mmog-development-part-1/).

##Dependencies

Premake4 is used to build the project.

Horde3D is used for graphics. Many of the default assets and graphics pipelines are also from Horde3D. The c++ math helper file, utMath.h, also comes from Horde3D with slight modifications.

GLFW is used for input as well as creating a OpenGL window.

Jansson is used for json parsing.

Python is used to generated json wrappers for components.

##Building
Sapling should mostly be cross platform, but it has only been tested on Linux.

To build simply run premake4 gmake. Then make in the main directory.

##License

All source is provided with absolutely no warranty and is under a [EPL](http://www.eclipse.org/legal/epl-v10.html) for now.

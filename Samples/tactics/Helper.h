#pragma once

#include <EntitySystem.h>

class Helper
{
  public:
    static Entity * getCamera();
    static Entity * getPlayerState();

    static void deselectAllTiles();
};

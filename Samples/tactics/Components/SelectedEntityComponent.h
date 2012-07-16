#pragma once
#include <EntitySystem.h>

struct SelectedEntityComponent : Component
{
  Entity *entity;
  SelectedEntityComponent();
};

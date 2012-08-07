#pragma once
#include <EntitySystem.h>

enum Resist
{
  kResistArmor,
  kResistMagicResist
};

struct UnitComponent : public Component
{
  int health;
  std::vector<float> resists;
  Entity *owner;

  void takeDamage(Resist type, float amount);
  UnitComponent();

};

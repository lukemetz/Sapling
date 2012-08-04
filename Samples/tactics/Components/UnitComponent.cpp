#include "UnitComponent.h"

UnitComponent::UnitComponent()
{
  health = 200;
  resists.resize(2, 0);
  resists[kResistArmor] = 10.f;
  resists[kResistMagicResist] = 5.0f;
}

void UnitComponent::takeDamage(Resist type, float amount)
{
  health = amount/(1+resists[type]/100.f);
}

#include "WobbleMoverSystem.h"
#include <GL/glfw.h>
#include "../App.h"

using namespace Component;

void WobbleMoverSystem::run(float dt)
{
  std::vector<Entity*> entities;
  ensys->getEntities<WobbleMover>(entities);
  for(Entity *entity : entities) {
    WobbleMover *wc = entity->getAs<WobbleMover>();
    Transform *tc = entity->getAs<Transform>();
    wc->time += dt;
    float cycle = wc->period*wc->time*(2.0f*Math::Pi);
    Vec3f delta = Vec3f(sinf(cycle+wc->offset.x),
                        sinf(cycle+wc->offset.y),
                        sinf(cycle+wc->offset.z));
    tc->pos += delta*wc->displacement*dt*2.0f*Math::Pi;
  }
}

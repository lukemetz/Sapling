#include "InputMoverSystem.h"

using namespace Component;

void InputMoverSystem::run(float dt)
{
	std::vector<Entity*> entities;
	ensys->getEntities<InputMover>(entities);
	InputMover *imc;
	Transform * tc;
	Input *ic;
	for(Entity* entity : entities) {
		imc = entity->getAs<InputMover>();
		tc = entity->getAs<Transform>();
		ic = entity->getAs<Input>();

		float curVel = imc->speed;

		if( ic->keys['W'] )
		{
			// Move forward
			tc->pos.x -= sinf( degToRad( tc->rot.y ) ) * cosf( -degToRad( tc->rot.x ) ) * curVel;
			tc->pos.y -= sinf( -degToRad( tc->rot.x ) ) * curVel;
			tc->pos.z -= cosf( degToRad( tc->rot.y ) ) * cosf( -degToRad( tc->rot.x ) ) * curVel;
		}
		if( ic->keys['S'] )
		{
			// Move backward
			tc->pos.x += sinf( degToRad( tc->rot.y ) ) * cosf( -degToRad( tc->rot.x ) ) * curVel;
			tc->pos.y += sinf( -degToRad( tc->rot.x ) ) * curVel;
			tc->pos.z += cosf( degToRad( tc->rot.y ) ) * cosf( -degToRad( tc->rot.x ) ) * curVel;
		}
		if( ic->keys['A'] )
		{
			// Strafe left
			tc->pos.x += sinf( degToRad( tc->rot.y - 90) ) * curVel;
			tc->pos.z += cosf( degToRad( tc->rot.y - 90 ) ) * curVel;
		}
		if( ic->keys['D'] )
		{
			// Strafe right
			tc->pos.x += sinf( degToRad( tc->rot.y + 90 ) ) * curVel;
			tc->pos.z += cosf( degToRad( tc->rot.y + 90 ) ) * curVel;
		}


		// Look left/right
		tc->rot.y -= (ic->mouseX-ic->prevMouseX) / 100 * 30;

		// Loop up/down but only in a limited range
		tc->rot.x -= (ic->mouseY-ic->prevMouseY) / 100 * 30;

		if( tc->rot.x > 90 ) tc->rot.x = 90;
		if( tc->rot.x < -90 ) tc->rot.x = -90;
	}
}

#include "RenderSystem.h"

RenderSystem::RenderSystem(EntitySystem *en)
{
  ensys = en;
}

void RenderSystem::run(float dt)
{
	std::vector<Entity*> entities;
	ensys->getEntities<CameraComponent>(entities);

	if(entities.size() != 1) {
		printf("ERROR in RenderSystem, More than one camera \n");
	}

	CameraComponent* cc;
	TransformComponent* tc;
  cc = entities[0]->getAs<CameraComponent>();
	tc = entities[0]->getAs<TransformComponent>();

	h3dSetNodeTransform( cc->node, tc->pos.x,   tc->pos.y,   tc->pos.z,
                                 tc->rot.x,   tc->rot.y,   tc->rot.z,
                                 tc->scale.x, tc->scale.y, tc->scale.z);
	std::vector<Entity*> meshes;
	ensys->getEntities<MeshComponent>(meshes);

  for(std::vector<Entity*>::iterator it = meshes.begin(); it!=meshes.end(); ++it) {
		MeshComponent *mc = (*it)->getAs<MeshComponent>();
		tc = (*it)->getAs<TransformComponent>();
    if (!tc)
      printf("RenderSystem requires a TransformComponent on the entity that has a CameraComponent \n");

		h3dSetNodeTransform( mc->node, tc->pos.x,   tc->pos.y,   tc->pos.z,
	    		          						   tc->rot.x,   tc->rot.y,   tc->rot.z,
			     					          	   tc->scale.x, tc->scale.y, tc->scale.z );
	}

  LightComponent *lc;
  std::vector<Entity*> lights;
  ensys->getEntities<LightComponent>(lights);
  for(std::vector<Entity*>::iterator it = lights.begin(); it != lights.end(); ++it) {
    lc = (*it)->getAs<LightComponent>();
    tc = (*it)->getAs<TransformComponent>();
    h3dSetNodeTransform( lc->node,  tc->pos.x,   tc->pos.y,   tc->pos.z,
                                    tc->rot.x,   tc->rot.y,   tc->rot.z,
                                    tc->scale.x, tc->scale.y, tc->scale.z );
    h3dSetNodeParamF(lc->node, H3DLight::RadiusF, 0, lc->radius);
    h3dSetNodeParamF(lc->node, H3DLight::FovF, 0, lc->fieldOfView);
    h3dSetNodeParamF(lc->node, H3DLight::ColorF3, 0, lc->color[0]);
    h3dSetNodeParamF(lc->node, H3DLight::ColorF3, 1, lc->color[1]);
    h3dSetNodeParamF(lc->node, H3DLight::ColorF3, 2, lc->color[2]);
  }

	h3dRender( cc->node );
	h3dFinalizeFrame();
	h3dClearOverlays();
	h3dutDumpMessages();
}

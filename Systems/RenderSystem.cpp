#include "RenderSystem.h"

RenderSystem::RenderSystem(EntitySystem *en)
{
  ensys = en;
}

CameraComponent* RenderSystem::runCamera(float dt)
{
	std::vector<Entity*> entities;
	ensys->getEntities<CameraComponent>(entities);

	if(entities.size() != 1) {
		printf("ERROR in RenderSystem, More than one camera \n");
	}

  CameraComponent* cc = entities[0]->getAs<CameraComponent>();
	TransformComponent* tc = entities[0]->getAs<TransformComponent>();

	h3dSetNodeTransform( cc->node, tc->pos.x,   tc->pos.y,   tc->pos.z,
                                 tc->rot.x,   tc->rot.y,   tc->rot.z,
                                 tc->scale.x, tc->scale.y, tc->scale.z);
  return cc;
}


void RenderSystem::runMeshes(float dt)
{
	std::vector<Entity*> meshes;
	ensys->getEntities<MeshComponent>(meshes);

  TransformComponent* tc;
  for(std::vector<Entity*>::iterator it = meshes.begin(); it!=meshes.end(); ++it) {
    MeshComponent *mc = (*it)->getAs<MeshComponent>();
    if (mc->oldPath != mc->path) {
      mc->res = h3dAddResource(H3DResTypes::SceneGraph, mc->path.c_str(), 0);
      std::string s = Application::appPath+"Content";
      h3dutLoadResourcesFromDisk(s.c_str());
      h3dRemoveNode(mc->node);
      mc->node = h3dAddNodes(H3DRootNode, mc->res);
      mc->oldPath = mc->path;
    }

		tc = (*it)->getAs<TransformComponent>();
    if (!tc)
      printf("RenderSystem requires a TransformComponent on the entity that has a CameraComponent \n");

		h3dSetNodeTransform( mc->node, tc->pos.x,   tc->pos.y,   tc->pos.z,
	    		          						   tc->rot.x,   tc->rot.y,   tc->rot.z,
			     					          	   tc->scale.x, tc->scale.y, tc->scale.z );
	}
}

void RenderSystem::runLights(float dt)
{
  LightComponent *lc;
  TransformComponent* tc;
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
}

void RenderSystem::run(float dt)
{
  CameraComponent *cc = runCamera(dt);
  runMeshes(dt);
  runLights(dt);

	h3dRender( cc->node );
	h3dFinalizeFrame();
	h3dClearOverlays();
	h3dutDumpMessages();
}

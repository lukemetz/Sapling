#include "RenderSystem.h"
#include "Utils.h"

RenderSystem::RenderSystem()
{
  ensys = EntitySystem::sharedInstance();
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

  Utils::sharedInstance()->addNodeEntity(cc->node, entities[0]);
  return cc;
}


void RenderSystem::runMeshes(float dt)
{
	std::vector<Entity*> meshes;
	ensys->getEntities<MeshComponent>(meshes);

  TransformComponent* tc;
  for(Entity * entity : meshes) {
    MeshComponent *mc = entity->getAs<MeshComponent>();
    if (mc->oldPath.compare(mc->path) != 0) {
      mc->res = h3dAddResource(H3DResTypes::SceneGraph, mc->path.c_str(), 0);
      std::string s = Application::appPath+"Content";
      h3dutLoadResourcesFromDisk(s.c_str());
      h3dRemoveNode(mc->node);
      mc->node = h3dAddNodes(H3DRootNode, mc->res);
      mc->oldPath = mc->path;
    }

		tc = entity->getAs<TransformComponent>();
    if (!tc)
      printf("RenderSystem requires a TransformComponent on the entity that has a CameraComponent \n");

		h3dSetNodeTransform( mc->node, tc->pos.x,   tc->pos.y,   tc->pos.z,
	    		          						   tc->rot.x,   tc->rot.y,   tc->rot.z,
			     					          	   tc->scale.x, tc->scale.y, tc->scale.z );
    printf("relating %d to en \n", mc->node);
    Utils::sharedInstance()->addNodeEntity(mc->node, entity);
  }
}


void RenderSystem::runLights(float dt)
{
  LightComponent *lc;
  TransformComponent* tc;
  std::vector<Entity*> lights;
  ensys->getEntities<LightComponent>(lights);
  for(Entity *entity : lights) {
    lc = entity->getAs<LightComponent>();
    tc = entity->getAs<TransformComponent>();
    h3dSetNodeTransform( lc->node,  tc->pos.x,   tc->pos.y,   tc->pos.z,
                                    tc->rot.x,   tc->rot.y,   tc->rot.z,
                                    tc->scale.x, tc->scale.y, tc->scale.z );
    h3dSetNodeParamF(lc->node, H3DLight::RadiusF, 0, lc->radius);
    h3dSetNodeParamF(lc->node, H3DLight::FovF, 0, lc->fieldOfView);
    h3dSetNodeParamF(lc->node, H3DLight::ColorF3, 0, lc->color[0]);
    h3dSetNodeParamF(lc->node, H3DLight::ColorF3, 1, lc->color[1]);
    h3dSetNodeParamF(lc->node, H3DLight::ColorF3, 2, lc->color[2]);
    Utils::sharedInstance()->addNodeEntity(lc->node, entity);
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

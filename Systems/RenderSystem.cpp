#include "RenderSystem.h"
#include "Utils.h"

using namespace Component;

RenderSystem::RenderSystem()
{
  ensys = EntitySystem::sharedInstance();
}

Camera* RenderSystem::runCamera(float dt)
{
	std::vector<Entity*> entities;
	ensys->getEntities<Camera>(entities);

	if(entities.size() != 1) {
		printf("ERROR in RenderSystem, More than one camera \n");
	}

  Camera* cc = entities[0]->getAs<Camera>();
	Transform* tc = entities[0]->getAs<Transform>();

	h3dSetNodeTransform( cc->node, tc->pos.x,   tc->pos.y,   tc->pos.z,
                                 tc->rot.x,   tc->rot.y,   tc->rot.z,
                                 tc->scale.x, tc->scale.y, tc->scale.z);

  Utils::sharedInstance()->addNodeEntity(cc->node, entities[0]);
  return cc;
}


void RenderSystem::runMeshes(float dt)
{
	std::vector<Entity*> meshes;
	ensys->getEntities<Mesh>(meshes);

  Transform* tc;
  for(Entity * entity : meshes) {
    Mesh *mc = entity->getAs<Mesh>();
    if (mc->oldPath.compare(mc->path) != 0) {
      mc->res = h3dAddResource(H3DResTypes::SceneGraph, mc->path.c_str(), 0);
      std::string s = Application::appPath+"Content";
      h3dutLoadResourcesFromDisk(s.c_str());
      h3dRemoveNode(mc->node);
      mc->node = h3dAddNodes(H3DRootNode, mc->res);
      mc->oldPath = mc->path;

      Utils::sharedInstance()->addNodeEntity(mc->node, entity);
    }

		tc = entity->getAs<Transform>();
    if (!tc)
      printf("RenderSystem requires a Transform Component on the entity that has a Camera Component \n");

		h3dSetNodeTransform( mc->node, tc->pos.x,   tc->pos.y,   tc->pos.z,
	    		          						   tc->rot.x,   tc->rot.y,   tc->rot.z,
			     					          	   tc->scale.x, tc->scale.y, tc->scale.z );
  }
}

void RenderSystem::runLights(float dt)
{
  Light *lc;
  Transform* tc;
  std::vector<Entity*> lights;
  ensys->getEntities<Light>(lights);
  for(Entity *entity : lights) {
    lc = entity->getAs<Light>();
    tc = entity->getAs<Transform>();
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
  Camera *cc = runCamera(dt);
  runMeshes(dt);
  runLights(dt);
  if (cc->debug) {
    h3dutShowFrameStats( cc->fontMatRes, cc->panelMatRes, 2);
  }

  h3dRender( cc->node );
	h3dFinalizeFrame();

	h3dClearOverlays();
	h3dutDumpMessages();
}

#include "Scene.h"

unsigned Scene::CreateEntity()
{
	auto entity = std::make_shared<Entity>();

	entityMap.emplace(entity->id, entity);

	return entity->id;
}

void Scene::Update()
{
	for (auto& item : systems)
	{
		item->Update();
	}
}

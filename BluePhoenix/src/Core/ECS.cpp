#include "ECS.hpp"

using namespace ecs;

Key contC = 1;

void Scene::Tick()
{
	for (auto item : activeSystems)
	{
		if (item != nullptr)
		{
			item->Tick();
		}
	}
}

unsigned Scene::addSystem(System* sys)
{
	systems.push_back(sys);
	activeSystems.push_back(sys);
	return contS++;
}

void Scene::deactivateSystem(unsigned pos)
{
	activeSystems.at(pos) = nullptr;
}

void Scene::activateSystem(unsigned pos)
{
	activeSystems.at(pos) = systems.at(pos);
}

Entity Scene::createEntity()
{
	entities.insert({ ++contE, 0 });
	return contE;
}

void ecs::Scene::destroyEntity(Entity ent)
{
	auto item = entities.find(ent);

	if (item == entities.end()) return;

	auto [id, key] = (*item);

	for (int i = 0; i < key.size(); i++)
	{
		if (key.test(i))
		{
			Key k;
			k.set(i);
			// TODO eliminar el componente del contenedor adecuado;
		}
	}

	for (auto item : systems)
	{
		if (item->hasEntity(ent))
		{
			item->removeEntity(ent);
		}
	}
}
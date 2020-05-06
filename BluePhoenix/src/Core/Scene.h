#pragma once

#include <vector>
#include <unordered_map>

#include "Entity.h"
#include "System.h"

namespace BP_ECS
{
	class Scene
	{
	private:
		std::unordered_map<unsigned, Entity*> entities;
		std::vector<System*> systems;
		unsigned entityCounter = 0;
	public:

		unsigned createEntity()
		{
			entities[entityCounter] = new Entity();
			return entityCounter++;
		}

		template<typename T>
		void addComponent(unsigned entity)
		{
			Entity* e = entities.at(entity);

			e->add<T>();

			for (auto item : systems)
			{
				if (item->filter(e))
					item->addEntity(e);
			}
		}

		void addSystem(System* s)
		{
			systems.push_back(s);
		}

		void Tick()
		{
			for (auto item : systems)
			{
				item->Tick();
			}
		}
	};
}

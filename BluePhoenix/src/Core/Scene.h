#pragma once

#include <vector>
#include <unordered_map>

#include "Entity.h"
#include "System.h"
#include "ComponentList.h"

namespace BP_ECS
{
	class Scene
	{
	private:
		std::unordered_map<unsigned, Entity*> entities;

		unordered_map<unsigned, ComponentList*> componentList;

		std::vector<System*> systems;
		unsigned entityCounter = 0;
	public:

		unsigned createEntity()
		{
			entities[++entityCounter] = new Entity();
			return entityCounter;
		}

		template<typename T>
		T* addComponent(unsigned entity)
		{
			unsigned type = getType<T>();
			auto item = componentList.find(type);			
			

			if (item == componentList.end()) // Si no hay un contenedor para ese tipo se crea
			{
				componentList.insert({ getType<T>() , new ComponentListTemplate<T>() });
			}

			ComponentList* cl = componentList.find(type)->second;

			Component* comp = cl->add();

			Entity* e = entities.at(entity);

			e->add(type, comp);

			for (auto item : systems)
			{
				if (item->filter(e))
					item->addEntity(e);
			}

			return dynamic_cast<T*>(comp);
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

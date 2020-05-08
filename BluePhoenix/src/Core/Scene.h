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

		template<typename T, typename... Args>
		void addComponent(unsigned entity, Args... args)
		{
			unsigned type = getType<T>();
			
			auto list = ComponentListTemplate<T>::getInstance();			

			auto item = componentList.find(type);

			if (item == componentList.end()) // Si no hay un contenedor para ese tipo se crea
			{
				componentList.insert({type , list});
			}

			Component* comp = list->add(args...);

			Entity* e = entities.at(entity);

			e->add(type, comp);

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

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
		unordered_map<unsigned, Entity*> entities;

		unordered_map<unsigned, ComponentList*> componentList;

		std::vector<System*> systems;
		unsigned entityCounter = 0;
	public:

		unsigned createEntity()
		{
			entities[++entityCounter] = new Entity();
			return entityCounter;
		}

		void removeEntity(unsigned entity)
		{
			auto elem = entities.find(entity);

			if (elem == entities.end()) return;

			for (auto item : systems)
			{
				if (item->hasEntity(entity))
				{
					item->removeEntity(entity);
				}					
			}

			Entity* e = elem->second;

			for (auto item : e->types)
			{
				componentList[item]->remove(entity);
			}

			delete e;

			entities.erase(entity);
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


		template<typename T, typename... Args>
		void addComponent(unsigned entity, Args... args)
		{
			unsigned type = getType<T>();
			
			ComponentListTemplate<T>* list = ComponentListTemplate<T>::Instance();

			auto item = componentList.find(type);

			if (item == componentList.end())
			{
				componentList.insert({type , list});
			}

			list->add(entity, args...);

			Entity* e = entities.at(entity);

			e->add(type);

			for (auto item : systems)
			{
				if (item->filter(e) && ! item->hasEntity(entity))
					item->addEntity(entity);
			}
		}
	};
}

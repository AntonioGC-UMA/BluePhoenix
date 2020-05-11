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
		std::vector<System*> activeSystems;
		unsigned entityCounter = 0;
		unsigned systemCounter = 0;
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

		unsigned addSystem(System* s)
		{
			systems.push_back(s);
			activeSystems.push_back(s);
			return systemCounter++;
		}

		void activateSystem(unsigned pos)
		{			
			activeSystems.at(pos) = systems.at(pos);
		}

		void deactivateSystem(unsigned pos)
		{
			activeSystems.at(pos) = nullptr;
		}

		void Tick()
		{
			for (auto item : activeSystems)
			{
				if (item != nullptr)
				{
					item->Tick();
				}
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

		template <typename T>
		void removeComponent(unsigned entity)
		{
			unsigned type = getType<T>();
			Entity* e = entities.at(entity);
			e->remove(type);
			ComponentListTemplate<T>::Instance()->remove(entity);

			for (auto item : systems)
			{
				if (!item->filter(e) && item->hasEntity(entity))
					item->removeEntity(entity);
			}
		}
	};
}

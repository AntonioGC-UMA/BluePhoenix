#pragma once

#include <vector>
#include <memory>

#include "Entity.h"
#include "System.h"


class Scene
{
	std::map<unsigned, std::shared_ptr<Entity>> entityMap;	// Mapa con todas las entidades y sus IDs
	
	std::vector<std::unique_ptr<System>> systems;		// Lista de sistemas


public:

	unsigned CreateEntity();

	void Update();
	
	void AddSystem(System* sys)
	{		
		systems.push_back(std::unique_ptr<System>(sys));
	}
	
	/*
	template<class T>
	void AddSystem(std::vector<unsigned> filter)
	{
		std::unique_ptr<System> s = std::dynamic_pointer_cast<System>(std::make_unique<T>(filter));

		systems.push_back(s);
	}
	*/
	template<class T>
	weak_ptr<T> AddComponent(unsigned entity)
	{
		std::shared_ptr<Entity> e = entityMap.find(entity)->second;
		std::weak_ptr<T> comp = e->addComponent<T>();

		for (auto& sys : systems)
		{
			if (sys->matches(e))
			{
				sys->addEntity(e);
			}
		}

		return comp;
	}

	template<class T>
	weak_ptr<T> RemoveComponent(unsigned entity)
	{
		std::shared_ptr<Entity> e = entityMap.find(entity)->second;
		std::weak_ptr<T> comp = e->addComponent<T>();

		for (auto& sys : systems)
		{
			if (sys.Valid(e))
			{
				// TODO si el
			}
		}

		return comp;
	}
};


#pragma once

#include "Entity.h"


class Scene;

struct System
{
	std::vector<std::pair<unsigned, std::vector<std::weak_ptr<Component>>>> components;

	std::vector<unsigned> filter;


	static Scene scene;

	virtual void Update() = 0;

	System(std::vector<unsigned> types);

	bool matches(std::shared_ptr<Entity> e);
	void addEntity(std::shared_ptr<Entity> e);
	//bool targetsEntity(unsigned entityID);
	void removeEntity(unsigned entityID);
};

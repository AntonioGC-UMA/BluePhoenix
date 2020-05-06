#include "Entity.h"
/*
unsigned Entity::idCounter = 0;

Entity::Entity()
{
	this->id = idCounter++;
}

Entity::~Entity()
{
	for (auto& item : components)
	{
		delete item.second;
	}
}

bool Entity::hasComponent(unsigned type)
{
	return components.find(type) != components.end();
}


Component* Entity::getComponent(std::vector<unsigned> types)
{
	vector<std::weak_ptr<Component>> res;

	for (unsigned u : types)
	{
		res.push_back(components.find(u)->second);
	}

	return res;
}*/
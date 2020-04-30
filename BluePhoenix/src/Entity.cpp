#include "Entity.h"

unsigned Entity::idCounter = 0;

Entity::Entity()
{
	this->id = idCounter++;
}

bool Entity::hasComponent(unsigned type)
{
	return components.find(type) != components.end();
}

vector<std::weak_ptr<Component>> Entity::getComponents(std::vector<unsigned> types)
{
	vector<std::weak_ptr<Component>> res;

	for (unsigned u : types)
	{
		res.push_back(components.find(u)->second);
	}

	return res;
}
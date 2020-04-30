#include "System.h"

System::System(std::vector<unsigned> types)
{
	filter = types;
}

bool System::matches(std::shared_ptr<Entity> e)
{
	for (unsigned type : filter)
	{
		if (!e->hasComponent(type))
			return false;
	}

	return true;
}
/*
bool System::targetsEntity(unsigned entityID)
{
	for (auto& item : components)
	{
		if (item.first == entityID)
			return true;
	}
	return false;
}*/

void System::addEntity(std::shared_ptr<Entity> e)
{	
	components.push_back(std::make_pair(e->id, e->getComponents(filter)));
}

void System::removeEntity(unsigned entityID)
{
	for (auto t = components.begin(); t != components.end(); ++t)
	{
		if (t->first == entityID)
		{
			std::iter_swap(t, components.end() - 1);
			components.pop_back();
			return;
		}
	}
}

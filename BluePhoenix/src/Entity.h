#pragma once

#include <memory>
#include <vector>
#include <map>


#include "Component.h"


class Entity : public enable_shared_from_this<Entity>
{
	std::map<unsigned, std::shared_ptr<Component>> components;

	static unsigned idCounter;

public:
	
	unsigned id;

	Entity();

	bool hasComponent(unsigned type);

	std::vector<std::weak_ptr<Component>> getComponents(std::vector<unsigned> types);


	template<class T>
	bool hasComponent();

	template<class T>
	std::shared_ptr<T> addComponent();

};

template<class T>
inline bool Entity::hasComponent()
{
	unsigned tipe = Component::setType<T>();

	return components.find(tipe) != components.end();
}

template<class T>
inline shared_ptr<T> Entity::addComponent()
{
	std::shared_ptr<T> t = std::make_shared<T>();

	components.emplace(BaseComponent<T>::type, t);

	return t;
}

#pragma once

#include <memory>
#include <vector>



#include "Component.h"

using namespace std;

class Entity : public enable_shared_from_this<Entity>
{
	vector<shared_ptr<Entity>> children;
	vector<shared_ptr<Component>> components;

	weak_ptr<Entity> parent;

public:
	
	template<class T>
	shared_ptr<T> getComponent();

	template<class T>
	shared_ptr<T> addNewComponent();

	void addChild(shared_ptr<Entity> e);
	void start();
	void update(const float dt);
	void lateUpdate();
};

template<class T>
inline shared_ptr<T> Entity::getComponent()
{
	unsigned tipe = Component::setType<T>();

	for (auto& c : components)
	{
		if (c->getType() == tipe)
		{			
			return dynamic_pointer_cast<T>(c);
		}
	}

	return shared_ptr<T>();
}

template<class T>
inline shared_ptr<T> Entity::addNewComponent()
{
	shared_ptr<T> t = make_shared<T>();

	t->entity = shared_from_this();
	components.push_back(t);

	return t;
}

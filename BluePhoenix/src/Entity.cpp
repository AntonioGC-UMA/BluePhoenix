#include "Entity.h"


void Entity::addChild(shared_ptr<Entity> e)
{
	e->parent = shared_from_this();
	children.push_back(e);
}

void Entity::start()
{
	for (auto& c : components)
	{
		c->start();
	}

	for (auto& c : children)
	{
		c->start();
	}
}

void Entity::update(const float dt)
{
	for (auto& c : components)
	{
		c->update(dt);
	}

	for (auto& c : children)
	{
		c->update(dt);
	}
}

void Entity::lateUpdate()
{
	for (auto& c : components)
	{
		c->lateUpdate();
	}

	for (auto& c : children)
	{
		c->lateUpdate();
	}
}

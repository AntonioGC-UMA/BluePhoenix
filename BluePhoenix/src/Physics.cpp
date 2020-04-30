#include "Physics.h"
#include "Entity.h"

Physics::Physics()
{
	vel = 0;
	t = weak_ptr<Transform>();
}

void Physics::start()
{
	t = entity.lock()->getComponent<Transform>();
}

void Physics::update(const float dt)
{
	shared_ptr<Transform> trans = t.lock();

    if (trans)
    {
        trans->x += vel;

        if (trans->x > 1)
        {
            trans->x = -1;
        }
    }
}
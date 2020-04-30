#include "Mover.h"

#include "Transform.h"
#include "Velocity.h"


void Mover::Update()
{ 
    for (auto& item : components)
    {
        shared_ptr<Transform> trans = std::dynamic_pointer_cast<Transform>(item.second[0].lock());
        shared_ptr<Velocity> vel = std::dynamic_pointer_cast<Velocity>(item.second[1].lock());

        if (trans)
        {
            trans->x += vel->x;

            if (trans->x > 1)
            {
                trans->x = -1;
            }
        }
    }

}

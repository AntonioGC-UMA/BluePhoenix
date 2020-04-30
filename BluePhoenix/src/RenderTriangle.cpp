#include "RenderTriangle.h"

#include "Transform.h"
#include "GL/glew.h"

void RenderTriangle::Update()
{
    for (auto& item : components)
    {
        shared_ptr<Transform> t = std::dynamic_pointer_cast<Transform>(item.second[0].lock());

        glBegin(GL_TRIANGLES);


        glVertex2f(t->x - 0.5, t->y - 0.5);
        glVertex2f(t->x + 0.5, t->y - 0.5);
        glVertex2f(t->x + 0, t->y + 0.5);

        glEnd();
    }

}
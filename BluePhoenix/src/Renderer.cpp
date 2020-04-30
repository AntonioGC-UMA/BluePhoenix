#include "Renderer.h"
#include "Transform.h"
#include "Entity.h"

#include "GL/glew.h"

void Renderer::lateUpdate()
{
    glBegin(GL_TRIANGLES);

    shared_ptr<Transform> t = entity.lock()->getComponent<Transform>();

    glVertex2f( t->x -0.5, t->y -0.5);
    glVertex2f(t->x + 0.5, t->y -0.5);
    glVertex2f(t->x +0, t->y +0.5);

    glEnd();
}
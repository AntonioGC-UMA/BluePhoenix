#include "RenderTriangle.h"

#include "Transform.h"
#include "GL/glew.h"


void RenderTriangle::Tick()
{
	for (auto& item : comp)
	{
		auto [t] = item;

		glBegin(GL_TRIANGLES);

		
		glVertex2f(t->x - 0.5, t->y - 0.5);
		glVertex2f(t->x + 0.5, t->y - 0.5);
		glVertex2f(t->x + 0  , t->y + 0.5);

		glEnd();
	}
}
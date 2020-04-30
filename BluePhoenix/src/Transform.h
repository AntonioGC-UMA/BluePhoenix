#pragma once

#include "Component.h"

#include <iostream>

struct Transform : public BaseComponent<Transform>
{
public:
	double x, y;

	Transform();
	
	void mostar()
	{
		std::cout << "Tipo:" << type << "  Posicion( "<< x << ", " << y << ")" << std::endl;
	}

};


#pragma once

#include "Component.h"
#include "Transform.h"
#include <iostream>

struct Physics : public BaseComponent<Physics>
{
public:
	double vel;

	weak_ptr<Transform> t;

	void mostrar()
	{		
		std::cout << "Tipo:" << type << "  Velocidad:" << vel << std::endl;
		t.lock()->mostar();
	}

	Physics();

	void update(const float dt) override;
	void lateUpdate() override {};
	void start() override;
};


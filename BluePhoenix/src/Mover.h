#pragma once

#include "System.h"


struct Mover : public System
{
	Mover(std::vector<unsigned> v) : System(v) {}
	void Update() override;
};


#pragma once

#include "System.h"

struct RenderTriangle : public System
{
	RenderTriangle(std::vector<unsigned> v) : System(v) {}
	void Update() override;
};


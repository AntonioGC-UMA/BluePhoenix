#pragma once

#include "Component.h"


class Renderer : public BaseComponent<Renderer>
{
	void update(const float dt) override {};
	void lateUpdate() override;
};


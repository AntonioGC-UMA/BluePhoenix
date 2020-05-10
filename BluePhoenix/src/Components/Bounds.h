#pragma once


struct Bounds
{
	Bounds(float r, float l) : right(r), left(l) {}

	float right = 1, left = -1;
};
#pragma once
#include "GameObject.h"
class PlatformObject : public GameObject
{
public:
	PlatformObject(sf::Vector2f _size, float r_b, float b_b) :GameObject(_size, r_b, b_b) {}
	void animate(const float& elapsed) {}
};


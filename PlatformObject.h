#pragma once
#include "GameObject.h"
class PlatformObject : public GameObject
{
public:
	PlatformObject(sf::Vector2f _size) :GameObject(_size) {}
	void animate(const float& elapsed,sf::Vector2f gravity) {}
};


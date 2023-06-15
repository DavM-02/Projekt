#pragma once
#include "GameObject.h"
class PlatformObject : public GameObject
{
private:
	bool isMovingPlatform = false;
public:
	PlatformObject(const sf::Vector2f& _size,const bool& _isMovingPlatform);
	PlatformObject(const sf::Vector2f& _pos,const sf::Vector2f& _size,const bool& _isMovingPlatform);
	void setMovingState(const bool& _isMovingPlatform);
	bool getMovingState();
	void animate(const float& elapsed, sf::Vector2f gravity);
};


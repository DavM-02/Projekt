#pragma once
#include "GameObject.h"
class PlayerObject : public GameObject
{
private:
	bool onGround = false;
public:
	PlayerObject(sf::Vector2f _size, sf::Vector2f _position) :GameObject(_size, _position) {}
	bool getOnGround();
	void setOnGround(bool);
	void animate(const float&,sf::Vector2f);
	void jump();
};


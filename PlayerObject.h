#pragma once
#include "GameObject.h"
class PlayerObject : public GameObject
{
private:
	bool onGround = false;
	int PointsNumber=0;
public:
	PlayerObject(sf::Vector2f _size, sf::Vector2f _position) :GameObject(_size, _position) {}
	bool getOnGround();
	int get_PointsNumber();
	void addPoints(const int& _pts);
	void setOnGround(bool);
	void animate(const float& elapsed);
	void jump();
};


#pragma once
#include "GameObject.h"
class PlayerObject : public GameObject
{
private:
	bool onGround = false;
public:
	PlayerObject(sf::Vector2f _size, sf::Vector2f _position, float r_b, float b_b) :GameObject(_size, _position, r_b, b_b) {}
	void animate(const float& elapsed)
	{
		move((velocity += gravity) * elapsed); //Dodaje do pozycji wartosc predkosci+grawitacji
	}
	void window_collision()
	{
		if (getPosition().x <= 0) //Kolizja z lewa sciana okna
		{
			setPosition(0, getPosition().y);
		}
		if (getPosition().y <= 0) //Kolizja z górna sciana okna
		{
			setPosition(getPosition().x, 0);
			velocity.y = 0;
		}
		if (getPosition().x + getGlobalBounds().width >= right_bound) //Kolizja z prawa sciana okna
		{
			setPosition(right_bound - getGlobalBounds().width, getPosition().y);
		}
		if (getPosition().y + getGlobalBounds().height >= bottom_bound) //Kolizja z dolna sciana okna
		{
			setPosition(getPosition().x, bottom_bound - getGlobalBounds().height);
			onGround = true;
		}
	}
	void jump()
	{
		if (onGround)
		{
			velocity.y = -1200; //Predkosc do góry
			onGround = false;
		}
	}
	bool getOnGround()
	{
		return onGround;
	}
	void setOnGround(bool _oG)
	{
		onGround = _oG;
	}
};


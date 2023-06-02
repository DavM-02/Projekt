#pragma once
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class GameObject : public sf::RectangleShape
{
protected:
	sf::Vector2f gravity = { 0.0,30.0 };
	sf::Vector2f velocity;
	float right_bound = 800, bottom_bound = 800;

public:
	GameObject(const sf::Vector2f&, const sf::Vector2f&, const float&, const float&);
	GameObject(const sf::Vector2f&, const float&, const float&);
	~GameObject() {}
	void set_velocity(sf::Vector2f);
	void set_velocityX(float);
	void set_velocityY(float);
	sf::Vector2f get_velocity();
	virtual void animate(const float& elapsed) = 0;
};


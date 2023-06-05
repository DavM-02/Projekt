#pragma once
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class GameObject : public sf::RectangleShape
{
protected:
	sf::Vector2f velocity;

public:
	GameObject(const sf::Vector2f&, const sf::Vector2f&);
	GameObject(const sf::Vector2f&);
	~GameObject() {}
	void set_velocity(sf::Vector2f);
	void set_velocityX(float);
	void set_velocityY(float);
	sf::Vector2f get_velocity();
	virtual void animate(const float&,sf::Vector2f) = 0;
};


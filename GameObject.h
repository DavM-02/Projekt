#pragma once
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class GameObject : public sf::RectangleShape
{
protected:
	sf::Vector2f velocity = { 0,0 };
	sf::Vector2f gravity = { 0.0,30.0 };
public:
	GameObject(const sf::Vector2f& _size, const sf::Vector2f& _position);
	GameObject(const sf::Vector2f& _size);
	~GameObject() {}
	void set_velocity(const sf::Vector2f& _velocity);
	void set_velocityX(const float& _velocity_x);
	void set_velocityY(const float& _velocity_y);
	sf::Vector2f get_velocity();
	virtual void animate(const float& elapsed)=0;
};


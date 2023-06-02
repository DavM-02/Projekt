#include "GameObject.h"
GameObject::GameObject(const sf::Vector2f& _size, const sf::Vector2f& _position, const float& r_b, const float& b_b) :RectangleShape(_size)
{
	setPosition(_position);
	right_bound = r_b;
	bottom_bound = b_b;
}
GameObject::GameObject(const sf::Vector2f& _size, const float& r_b, const float& b_b) :RectangleShape(_size)
{
	right_bound = r_b;
	bottom_bound = b_b;
}
void GameObject::set_velocity(sf::Vector2f _velocity)
{
	velocity = _velocity;
}
void GameObject::set_velocityX(float _velocity_x)
{
	velocity.x = _velocity_x;
}
void GameObject::set_velocityY(float _velocity_y)
{
	velocity.y = _velocity_y;
}
sf::Vector2f GameObject::get_velocity()
{
	return velocity;
}
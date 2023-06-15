#include "PlatformObject.h"
PlatformObject::PlatformObject(const sf::Vector2f& _size, const bool& _isMovingPlatform) :GameObject(_size)
{
	isMovingPlatform = _isMovingPlatform;
	if (_isMovingPlatform)
		velocity.x = 250.0;
}
PlatformObject::PlatformObject(const sf::Vector2f& _pos, const sf::Vector2f& _size, const bool& _isMovingPlatform) :GameObject(_size)
{
	setPosition(_pos);
	isMovingPlatform = _isMovingPlatform;
	if (_isMovingPlatform)
		velocity.x = 250.0;
}
void PlatformObject::setMovingState(const bool& _isMovingPlatform)
{
	isMovingPlatform = _isMovingPlatform;
	velocity.x = 250;
}
bool PlatformObject::getMovingState()
{
	return isMovingPlatform;
}
void PlatformObject::animate(const float& elapsed, sf::Vector2f gravity)
{
	move(velocity * elapsed);
}
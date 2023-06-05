#include "PlayerObject.h"
bool PlayerObject::getOnGround()
{
	return onGround;
}
void PlayerObject::setOnGround(bool _oG)
{
	onGround = _oG;
}
void PlayerObject::animate(const float& elapsed,sf::Vector2f gravity)
{
	float old_pos = getPosition().y;
	move((velocity += gravity) * elapsed); //Dodaje do pozycji wartosc predkosci+grawitacji
	float new_pos = getPosition().y;
	if (new_pos != old_pos)
		onGround = false;
}
void PlayerObject::jump()
{
	if (onGround)
	{
		velocity.y = -1500; //Predkosc do góry
		onGround = false;
	}
}

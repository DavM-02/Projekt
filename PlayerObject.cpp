#include "PlayerObject.h"
bool PlayerObject::getOnGround()
{
	return onGround;
}
void PlayerObject::addPoints(const int& _pts)
{
	PointsNumber += _pts;
}
int PlayerObject::get_PointsNumber()
{
	return PointsNumber;
}
void PlayerObject::setOnGround(bool _oG)
{
	onGround = _oG;
}
void PlayerObject::animate(const float& elapsed,sf::Vector2f gravity)
{
	float old_height = getPosition().y;
    move((velocity += gravity) * elapsed); //Dodaje do pozycji wartosc predkosci+grawitacji
	float new_height = getPosition().y;
	if (new_height != old_height)
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

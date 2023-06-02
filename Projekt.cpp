#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "PlatformObject.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 900), "Program SFML");
	Game* game = new Game(window);
	game->gameLoop();
	return 0;
}
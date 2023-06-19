#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "PlatformObject.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 900), "Platformówka SFML");
	std::string menu_texture = "menu_giery.png";
	Game* game = new Game(window, menu_texture);
	game->gameLoop();
	delete game;
	return 0;
}
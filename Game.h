#pragma once
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "PlatformObject.h"
#include "PlayerObject.h"
#include "GameObject.h"
class Game
{
private:
	sf::RenderWindow& window;
	std::vector<PlatformObject*> platforms;
	PlayerObject* player;
	sf::Clock clock;
	sf::Event event;
public:
	Game(sf::RenderWindow&);
	~Game() {}
	sf::RenderWindow& getWindow();
	void gameLoop();
	void collision();
	void window_collision();
	std::vector<PlatformObject*> create_platforms();
};


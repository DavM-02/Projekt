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
	void gameLoop();
	void collision(const std::vector<PlatformObject*>&, PlayerObject*);
	std::vector<PlatformObject*> create_platforms();
};


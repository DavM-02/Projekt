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
	sf::View view;
	std::vector<PlatformObject*> platforms;
	PlayerObject* player;
	sf::Clock clock;
	sf::Event event;
	sf::Vector2f gravity = { 0.0,30.0 };
public:
	Game(sf::RenderWindow&);
	~Game() {}
	sf::RenderWindow& getWindow();
	sf::Vector2f get_gravity();
	void gameLoop();
	void move_window(const float&);
	void collision();
	void window_collision();
	std::vector<PlatformObject*> create_platforms();
};


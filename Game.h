#pragma once
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "PlatformObject.h"
#include "PlayerObject.h"
#include "GameObject.h"
#include "Menu.h"
#include "Round.h"

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
    Menu* menu;
    std::vector<sf::RectangleShape>imported_textures;
    Round* round;
    bool enter_to_game = false;
    bool is_new_round = false;
    bool end_of_the_game = false;
    int actual_level = 0;
public:
    Game(sf::RenderWindow&, std::string _menu_texture);
	~Game() {}
	sf::RenderWindow& getWindow();
	sf::Vector2f get_gravity();
	void gameLoop();
    void move_window();
	void collision(const float& elapsed);
	void window_collision();
    void new_round();
    void round_end();
    void end_of_game();
	std::vector<PlatformObject*> create_platforms();
};


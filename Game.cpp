#include "Game.h"
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
Game::Game(sf::RenderWindow& _win) : window(_win)
{
	window.setFramerateLimit(120);
	player = new PlayerObject({ 60.0,60.0 }, { 400.0,400.0 }, window.getSize().x, window.getSize().y);
	platforms = create_platforms(); //Tworzymy wektor platform i zapisujemy tam platformy utworzone za pomoca funkcji
}
void Game::gameLoop()
{
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) //Sprawdza czy zostala wscisnieta spacja
			{
				player->jump();
			}
		}
		//Sprawdza czy przyciski lewo/prawo sa wcisniete (jest róznica miêdzy tymi ifami a ifem ze spacji)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			player->set_velocityX(300);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			player->set_velocityX(-300);
		else
			player->set_velocityX(0);
		float elapsed = clock.restart().asSeconds(); //Czas pomiedzy wygenerowanymi klatkami
		//Ruch gracza i sprawdzanie kolizji z oknem i platformami
		player->animate(elapsed);
		player->window_collision();
		collision(platforms, player);


		window.clear(sf::Color::Black);
		for (int i = 0; i < platforms.size(); i++)
		{
			window.draw(*platforms[i]);
		}
		window.draw(*player);
		window.display();
	}

	delete player;
}
void Game::collision(const std::vector<PlatformObject*>& platforms, PlayerObject* player)
{
	for (int i = 0; i < platforms.size(); i++)
	{
		if (player->getGlobalBounds().intersects(platforms[i]->getGlobalBounds()))
		{
			float player_top = player->getGlobalBounds().top; //Górna wspólrzedna gracza
			float player_bot = player->getGlobalBounds().top + player->getGlobalBounds().height; //Dolna wspólrzedna gracza
			float player_left = player->getGlobalBounds().left; //Lewa wspólrzedna gracza
			float player_right = player->getGlobalBounds().left + player->getGlobalBounds().width; // Prawa wspólrzedna gracza
			float platform_top = platforms[i]->getGlobalBounds().top; //Górna wspólrzedna platformy
			float platform_bot = platforms[i]->getGlobalBounds().top + platforms[i]->getGlobalBounds().height; // Dolna wspólrzedna platformy
			float platform_left = platforms[i]->getGlobalBounds().left; //Lewa wspólrzêdna platformy
			float platform_right = platforms[i]->getGlobalBounds().left + platforms[i]->getGlobalBounds().width; //Prawa wspólrzedna platformy;

			if (player_bot > platform_top && player_top < platform_top) //Kolizja od góry
			{
				player->setPosition(player->getPosition().x, platforms[i]->getGlobalBounds().top - player->getGlobalBounds().height);
				player->setOnGround(true);
				player->set_velocityY(0);
				std::cout << "gora" << std::endl;
			}
			else if (player_top < platform_bot) //Kolizja od dolu
			{
				std::cout << "dol" << std::endl;
				player->setPosition(player->getPosition().x, platform_bot);
				player->set_velocityY(0);
			}
			/*Kolizja horyzontalna do zrobienia
			else if (player_left < platform_right && player_right>platform_right)
			{
				std::cout << "prawo" << std::endl;
				player->setPosition(platform_right, player->getPosition().y);
				player->velocity.x = 0;
			}
			else if (player_right > platform_left)
			{
				std::cout << "lewo" << std::endl;
				player->setPosition(platform_left, player->getPosition().y);
				player->velocity.x = 0;
			}
			*/

		}
	}
}
std::vector<PlatformObject*> Game::create_platforms()
{
	float position_x = 0;
	float position_y = 750;
	srand((unsigned)time(0));
	int acc = 0;
	std::vector<PlatformObject*> platforms;
	while (position_y >= 80)
	{
		PlatformObject* platform = new PlatformObject({ 130.0,18.0 }, 900, 900); //Zamiast platformy jako RectangleShape robimy platformy jako PlatformObject
		float tmp = rand() % 780;
		if (acc >= 1) //aby w miare rozsadnych odleglosciach sie te platformy respily xD
		{
			if (((std::abs(tmp - position_x)) >= 0) && ((std::abs(tmp - position_x)) <= 130))
			{
				if ((tmp - position_x) >= 0)
				{
					position_x = tmp + 120.f;
				}
				else if ((tmp - position_x) < 0)
				{
					position_x = tmp - 120.f;
				}
			}
			else if ((std::abs(tmp - position_x)) > 360)
			{
				if ((tmp - position_x) >= 0)
				{
					position_x = tmp - 180.f;
				}
				else if ((tmp - position_x) < 0)
				{
					position_x = tmp + 180.f;
				}
			}
			else if ((std::abs(tmp - position_x)) > 130)
			{
				position_x = tmp;
			}
		}
		else
		{
			position_x = tmp;
		}                                                                // dotad
		platform->setPosition(position_x, position_y);
		platform->setFillColor(sf::Color::Magenta);
		position_y = position_y - 220;
		platforms.emplace_back(std::move(platform));
		acc++;
	}
	return platforms;
}
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class GameObject : public sf::RectangleShape
{
protected:
	sf::Vector2f gravity = { 0.0,30.0 };
	sf::Vector2f velocity;
	float right_bound = 800, bottom_bound = 800;

public:
	GameObject(const sf::Vector2f& _size, const sf::Vector2f& _position, const float& r_b, const float& b_b) :RectangleShape(_size)
	{
		setPosition(_position);
		right_bound = r_b;
		bottom_bound = b_b;

	}
	GameObject(const sf::Vector2f& _size, const float& r_b, const float& b_b) :RectangleShape(_size)
	{
		right_bound = r_b;
		bottom_bound = b_b;
	}
	~GameObject() {}
	void set_velocity(sf::Vector2f _velocity)
	{
		velocity = _velocity;
	}
	void set_velocityX(float _velocity_x)
	{
		velocity.x = _velocity_x;
	}
	void set_velocityY(float _velocity_y)
	{
		velocity.y = _velocity_y;
	}
	sf::Vector2f get_velocity()
	{
		return velocity;
	}
	virtual void animate(const float& elapsed) = 0;
};
class PlayerObject : public GameObject
{
private:
	bool onGround = true;
public:
	PlayerObject(sf::Vector2f _size, sf::Vector2f _position, float r_b, float b_b) :GameObject(_size, _position, r_b, b_b) {}
	void animate(const float& elapsed)
	{
		move((velocity += gravity) * elapsed); //Dodaje do pozycji wartoœæ prêdkoœci+grawitacji
	}
	void window_collision()
	{
		if (getPosition().x <= 0) //Kolizja z lew¹ œcian¹ okna
		{
			setPosition(0, getPosition().y);
		}
		if (getPosition().y <= 0) //Kolizja z górn¹ œcian¹ okna
		{
			setPosition(getPosition().x, 0);
			velocity.y = 0;
		}
		if (getPosition().x + getGlobalBounds().width >= right_bound) //Kolizja z praw¹ œcian¹ okna
		{
			setPosition(right_bound - getGlobalBounds().width, getPosition().y);
		}
		if (getPosition().y + getGlobalBounds().height >= bottom_bound) //Kolizja z doln¹ œcian¹ okna
		{
			setPosition(getPosition().x, bottom_bound - getGlobalBounds().height);
			onGround = true;
		}
	}
	void jump()
	{
		if (onGround)
		{
			velocity.y = -1200; //Prêdkoœæ do góry
			onGround = false;
		}
	}
	bool getOnGround()
	{
		return onGround;
	}
	void setOnGround(bool _oG)
	{
		onGround = _oG;
	}
};
class PlatformObject : public GameObject
{
public:
	PlatformObject(sf::Vector2f _size, float r_b, float b_b) :GameObject(_size, r_b, b_b) {}
	void animate(const float& elapsed) {}
};

void collision(const std::vector<PlatformObject*>& platforms, PlayerObject* player)
{
	for (int i = 0; i < platforms.size(); i++)
	{
		if (player->getGlobalBounds().intersects(platforms[i]->getGlobalBounds()))
		{
			float player_top = player->getGlobalBounds().top; //Górna wspó³rzêdna gracza
			float player_bot = player->getGlobalBounds().top + player->getGlobalBounds().height; //Dolna wspó³rzêdna gracza
			float player_left = player->getGlobalBounds().left; //Lewa wspó³rzêdna gracza
			float player_right = player->getGlobalBounds().left + player->getGlobalBounds().width; // Prawa wspó³rzêdna gracza
			float platform_top = platforms[i]->getGlobalBounds().top; //Górna wspó³rzêdna platformy
			float platform_bot = platforms[i]->getGlobalBounds().top + platforms[i]->getGlobalBounds().height; // Dolna wspó³rzêdna platformy
			float platform_left = platforms[i]->getGlobalBounds().left; //Lewa wspó³rzêdna platformy
			float platform_right = platforms[i]->getGlobalBounds().left + platforms[i]->getGlobalBounds().width; //Prawa wspó³rzêdna platformy;
			if (player_bot > platform_top && player_top < platform_top) //Kolizja od góry
			{
				player->setPosition(player->getPosition().x, platforms[i]->getGlobalBounds().top - player->getGlobalBounds().height);
				player->setOnGround(true);
				player->set_velocityY(0);
				std::cout << "gora" << std::endl;
			}
			else if (player_top < platform_bot) //Kolizja od do³u
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

std::vector<PlatformObject*> create_platforms()
{
	float position_x = 0;
	float position_y = 750;
	srand((unsigned)time(0));
	int acc = 0;
	std::vector<PlatformObject*> platforms;
	while (position_y >= 80)
	{
		PlatformObject* platform = new PlatformObject({ 130.0,18.0 }, 900, 900); //Zamiast platformy jako RectangleShape robimy platformy jako PlatformObject
		int tmp = rand() % 780;
		if (acc >= 1) //aby w miare rozsadnych odleglosciach sie te platformy respily xD
		{
			if (((std::abs(tmp - position_x)) >= 0) && ((std::abs(tmp - position_x)) <= 130))
			{
				if ((tmp - position_x) >= 0)
				{
					position_x = tmp + 120;
				}
				else if ((tmp - position_x) < 0)
				{
					position_x = tmp - 120;
				}
			}
			else if ((std::abs(tmp - position_x)) > 360)
			{
				if ((tmp - position_x) >= 0)
				{
					position_x = tmp - 180;
				}
				else if ((tmp - position_x) < 0)
				{
					position_x = tmp + 180;
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
int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 900), "Program SFML");
	sf::Clock clock;
	window.setFramerateLimit(120);
	PlayerObject* player = new PlayerObject({ 60.0,60.0 }, { 400.0,400.0 }, window.getSize().x, window.getSize().y);
	std::vector<PlatformObject*> platforms = create_platforms(); //Tworzymy wektor platform i zapisujemy tam platformy utworzone za pomoca funkcji

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) //Sprawdza czy zosta³a wscisnieta spacja
			{
				player->jump();
			}
		}
		//Sprawdza czy przyciski lewo/prawo s¹ wciœniete (jest ró¿nica miêdzy tymi ifami a ifem ze spacj¹)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			player->set_velocityX(300);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			player->set_velocityX(-300);
		else
			player->set_velocityX(0);
		float elapsed = clock.restart().asSeconds(); //Czas pomiêdzy wygenerowanymi klatkami
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
	return 0;
}
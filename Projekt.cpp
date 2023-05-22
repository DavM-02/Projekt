#include <iostream>
#include<memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class GameObject : public sf::RectangleShape
{
protected:
	sf::Vector2f size, position;
	float left_bound = 0, right_bound = 600, top_bound = 0, bottom_bound = 600;

public:
	GameObject(const sf::Vector2f& _size, const sf::Vector2f& _position, const float& r_b, const float& b_b) :RectangleShape(_size)
	{
		size = _size;
		position = _position;
		right_bound = r_b;
		bottom_bound = b_b;
		setPosition(position);
		setBounds(0, right_bound, 0, bottom_bound);
	}
	~GameObject() {}
	void setBounds(const float& l_b, const float& r_b, const float& t_b, const float& b_b)
	{
		left_bound = l_b;
		right_bound = r_b - size.x;
		top_bound = t_b;
		bottom_bound = b_b - size.y;
	}
	virtual void animate(const sf::Time& elapsed, sf::Event& event) = 0;
};
class PlayerObject : public GameObject
{
public:
	PlayerObject(sf::Vector2f _size, sf::Vector2f _position, float r_b, float b_b) : GameObject(_size, _position, r_b, b_b) {}
	void animate(const sf::Time& elapsed, sf::Event& event)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			setPosition(position.x -= 0.2, position.y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			setPosition(position.x += 0.2, position.y);
		}
	}
};
class PlatformObject : public GameObject
{
public:
	PlatformObject(sf::Vector2f _size, sf::Vector2f _position, float r_b, float b_b) :GameObject(_size, _position, r_b, b_b) {}
	void animate(const sf::Time& elapsed, sf::Event& event) {}
};

class Board
{
private:
	std::shared_ptr<GameObject>player;
	sf::RenderWindow window;
public:
	Board(std::shared_ptr<GameObject>_obj, sf::Vector2i size) : player(_obj),window(sf::VideoMode(size.x, size.y),"Gra")
	{
		while (window.isOpen())
		{
			sf::Event event;
			window.clear(sf::Color::Black);
			sf::Clock clock;
			sf::Time elapsed = clock.restart();
			player->animate(elapsed, event);
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}
			window.draw(*player);
			window.display();
		}
	};
};


int main()
{
	sf::Vector2i window_size(600, 600);
	sf::Vector2f size(60.0, 60.0);
	sf::Vector2f position(300.0, 300.0);
	std::shared_ptr<GameObject>player = std::make_shared<PlayerObject>(size, position, 600, 600);
	Board board1(player,window_size);

	return 0;
}
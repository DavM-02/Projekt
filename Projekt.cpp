#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class GameObject : public sf::RectangleShape
{
protected:
	sf::Vector2f size,position;
	float left_bound=0, right_bound=600, top_bound=0, bottom_bound=600;

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
	void setBounds(const float& l_b,const float& r_b, const float& t_b,const float& b_b) 
	{
		left_bound = l_b;
		right_bound = r_b-size.x;
		top_bound = t_b;
		bottom_bound = b_b-size.y;
	}
	virtual void animate(const sf::Time& elapsed, sf::Event& event) = 0;
};
class PlayerObject : public GameObject
{
public:
	PlayerObject(sf::Vector2f _size, sf::Vector2f _position, float r_b, float b_b) :GameObject(_size, _position, r_b, b_b) {}
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


int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Program SFML");
	sf::Vector2f size(60.0, 60.0);
	sf::Vector2f position(300.0, 300.0);
	GameObject* player=new PlayerObject(size, position,window.getPosition().x,window.getPosition().y);

	while (window.isOpen()) 
	{
		sf::Event event;
		window.clear(sf::Color::Black);
		sf::Clock clock;
		sf::Time elapsed = clock.restart();
		player->animate(elapsed,event);
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
	delete player;
	return 0;
}
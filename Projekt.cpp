#include <iostream>
#include<memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include<cmath>

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
        left_bound = r_b - l_b;
        right_bound = size.x;
        top_bound = t_b;
        bottom_bound = b_b - size.y;
    }
    virtual void animate(const sf::Time& elapsed, sf::Event& event) = 0;
};
class PlayerObject : public GameObject
{
private:
    float velocity_x = 0.2;
    float velocity_y = 0.5;
public:
    PlayerObject(sf::Vector2f _size, sf::Vector2f _position, float r_b, float b_b) : GameObject(_size, _position, r_b, b_b) {}
    void animate(const sf::Time& elapsed, sf::Event& event)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            setPosition(position.x -= velocity_x, position.y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            setPosition(position.x += velocity_x, position.y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            setPosition(position.x, position.y -= velocity_y);
        }
        else
        {

        }
    }
};
class PlatformObject : public GameObject
{
private:

public:
    PlatformObject(sf::Vector2f _size, sf::Vector2f _position, float r_b, float b_b) : GameObject(_size, _position, r_b, b_b) {}
    void animate(const sf::Time& elapsed, sf::Event& event) {}

};

class Board
{
private:
    std::shared_ptr<GameObject>player;
    sf::RenderWindow window;
    std::vector<std::unique_ptr<sf::RectangleShape>>platforms;
public:
    Board(std::shared_ptr<GameObject>_obj, sf::Vector2i size) : player(_obj),window(sf::VideoMode(size.x, size.y),"Gra")
    {

        create_platforms();
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
            for(int i = 0; i < platforms.size();i++)
            {
                window.draw(*platforms[i]); //tworzenie platform na planszy
            }
            window.draw(*player);
            window.display();
        }
    };
    void create_platforms()
    {
        float position_x = 0;
        float position_y = 750;
        srand((unsigned)time(0));
        int acc=0;

        while(position_y >=80)
        {
            std::unique_ptr<sf::RectangleShape>platform = std::make_unique<sf::RectangleShape>(sf::Vector2f(130.0,18.0));
            int tmp = rand()%780;
            if(acc >=1) //aby w miare rozsadnych odleglosciach sie te platformy respily xD
            {
                if(((std::abs(tmp-position_x)) >= 0) && ((std::abs(tmp-position_x)) <= 130))
                {
                    if((tmp-position_x) >= 0)
                    {
                        position_x = tmp+120;
                    }
                    else if((tmp-position_x) < 0)
                    {
                        position_x = tmp-120;
                    }
                }
                else if((std::abs(tmp-position_x)) > 360)
                {
                    if((tmp-position_x) >= 0)
                    {
                        position_x = tmp-180;
                    }
                    else if((tmp-position_x) < 0)
                    {
                        position_x = tmp+180;
                    }
                }
                else if((std::abs(tmp-position_x)) > 130)
                {
                    position_x = tmp;
                }

            }
            else
            {
                position_x = tmp;
            }
            platform->setPosition(position_x,position_y);
            platform->setFillColor(sf::Color::Magenta);
            position_y = position_y-220;
            platforms.emplace_back(std::move(platform));
            acc++;
        }
    }
};


int main()
{
    sf::Vector2i window_size(900, 900);
    sf::Vector2f size(60.0, 60.0);
    sf::Vector2f position(420.0, 840.0);
    std::shared_ptr<GameObject>player = std::make_shared<PlayerObject>(size, position, 600, 600);
    Board board1(player,window_size);


    return 0;
}

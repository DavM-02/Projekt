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
    std::vector<float>bottom_bounds;
    std::vector<float>upper_bounds;
    std::vector<sf::Vector2f>left_and_upper_bounds;
    std::vector<float>left_bounds;
    std::vector<float>right_bounds;
    std::vector<sf::Vector2f>right_and_bottom_bounds;
    bool space_pressed = 0;
    bool out_of_platform = 0;
    int sign = 1;
    bool stopped_in_platform = 0;
public:
    PlayerObject(sf::Vector2f _size, sf::Vector2f _position, float r_b, float b_b) : GameObject(_size, _position, r_b, b_b) {}

    void set_vectors(std::vector<sf::Vector2f> tmp) // zapis polozen platform do wektorow
    {
        for(int i=0;i<tmp.size();i++)
        {
            left_and_upper_bounds.emplace_back(sf::Vector2f(tmp[i].x,tmp[i].y));
            right_and_bottom_bounds.emplace_back(tmp[i].x+130,tmp[i].y+18);
        }
    }

    void animate(const sf::Time& elapsed, sf::Event& event)
    {
        int multp = 1;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            space_pressed = 1; //zmiana na 1 gdy spacja zostanie wcisnieta - potrzebne do petli implementujacej skok
        }

        for(int i=0;i<left_and_upper_bounds.size();i++)
        {
            if((int(getPosition().y) == right_and_bottom_bounds[i].y) && ((int(getPosition().x+60) >= left_and_upper_bounds[i].x) && (int(getPosition().x) <= right_and_bottom_bounds[i].x)))
            {
                sign = -sign; //dotkniecie platformy od spodu
            }
            if((int(getPosition().x+60) == left_and_upper_bounds[i].x) && ((int(getPosition().y) < right_and_bottom_bounds[i].y) && (int(getPosition().y+60) > left_and_upper_bounds[i].y)))
            {
                multp = 0; //dotkniecie platformy od lewej
            }
            if((int(getPosition().x) == right_and_bottom_bounds[i].x) && ((int(getPosition().y) < right_and_bottom_bounds[i].y) && (int(getPosition().y+60) > left_and_upper_bounds[i].y)))
            {
                multp = 0; //dotkniecie platformy od prawej
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            setPosition(position.x -= multp*velocity_x, position.y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            setPosition(position.x += multp*velocity_x, position.y);
        }
        if (space_pressed)
        {
            static float zm = 0; //zmienna wykorzystywana przy okreslaniu predkosci
            if(sign < 0)
            {
                zm--;
            }
            else
            {
                zm++;
            }
            setPosition(position.x, position.y -= sign*(velocity_y-(zm/3000)));
            std::cerr << (velocity_y-(zm/3000)) <<std::endl;
            if(position.y > 840) //stop gdy kwadrat dotknie podloza
            {
                setPosition(position.x, position.y);
                sign = 1;
                space_pressed = 0;
                zm = 0;
            }
            for(int i=0;i<left_and_upper_bounds.size();i++)
            {
                if((int(position.y+60) == left_and_upper_bounds[i].y) && (sign*(velocity_y-(zm/3000)) < 0) && ((int(getPosition().x+60) >= left_and_upper_bounds[i].x) && (int(getPosition().x) <= right_and_bottom_bounds[i].x)))
                {
                    setPosition(position.x, position.y);
                    sign = 1;
                    space_pressed = 0;
                    zm = 0;
                    stopped_in_platform = 1;
                }
            }
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
    std::shared_ptr<PlayerObject>player;
    sf::RenderWindow window;
    std::vector<std::unique_ptr<sf::RectangleShape>>platforms;
public:
    Board(sf::Vector2i size_) : window(sf::VideoMode(size_.x, size_.y),"Gra")
    {
        sf::Vector2f size(60.0, 60.0);
        sf::Vector2f position(420.0, 840.0);
        player = std::make_shared<PlayerObject>(size, position, 600, 600);
        create_platforms();
        player->set_vectors(get_bounds());

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
            }                                                                // dotad
            platform->setPosition(position_x,position_y);
            platform->setFillColor(sf::Color::Magenta);
            position_y = position_y-220;
            platforms.emplace_back(std::move(platform));
            acc++;
        }
    }
    std::vector<sf::Vector2f> get_bounds()
    {
        std::vector<sf::Vector2f> tmp;
        for(int i=0;i<platforms.size();i++)
        {
            tmp.emplace_back(platforms[i]->getPosition());
        }
        return tmp;
    }
};


int main()
{
    sf::Vector2i window_size(900, 900);
    sf::Vector2f size(60.0, 60.0);
    sf::Vector2f position(420.0, 840.0);
    //std::shared_ptr<PlayerObject>player = std::make_shared<PlayerObject>(size, position, 600, 600);
    //Board board1(*player, window_size);
    Board board1(window_size);
    //player->set_vectors(board1.get_bounds());

    return 0;
}


#include "bonus.h"

Bonus::Bonus()
{
    set_coin();
}

void Bonus::set_coin()
{
    srand (time(NULL));
    this->coin = new sf::Texture();
    coin->loadFromFile("coin.png");
}

void Bonus::generate_coins(std::vector<float> coord_y)
{
    srand (time(NULL));
    int acc = 0;
    for(int i=2;i < coord_y.size()-1;i=i+3)
    {
        float _y = coord_y[i+1]-(coord_y[i+1]-coord_y[i])/2;
        sf::RectangleShape* bon = new sf::RectangleShape(sf::Vector2f(1238,1300));
        bon->setTexture(this->coin);
        bon->scale(sf::Vector2f(0.05, 0.05));
        acc++;
        bon->setPosition(sf::Vector2f(5+(rand()%890+acc*400)%855,_y));
        coins.emplace_back(*bon);
    }
}

void Bonus::draw_coins(sf::RenderWindow& _window, sf::FloatRect player_coord)
{
    if(player_coord.intersects(coins[0].getGlobalBounds()))
    {
        this->touched_first = true;
    }
    if(player_coord.intersects(coins[1].getGlobalBounds()))
    {
        this->touched_second = true;
    }

    if(touched_first != true)
    {
        _window.draw(coins[0]);
    }
    else
    {
        if(this->first_bonus_added == false)
        {
            add_bonus();
            first_bonus_added = true;
        }
        sf::Font font;
        if (!font.loadFromFile("Minecraft.ttf"))
        {
            throw("Missing font file!");
        }
        sf::Text * text= new sf::Text("+200",font,28);
        text->setFillColor(sf::Color::Yellow);
        text->setPosition(coins[0].getPosition());
        _window.draw(*text);
    }
    if(touched_second != true)
    {
        _window.draw(coins[1]);
    }
    else
    {
        if(this->second_bonus_added == false)
        {
            add_bonus();
            second_bonus_added = true;
        }
        sf::Font font;
        if (!font.loadFromFile("Minecraft.ttf"))
        {
            throw("Missing font file!");
        }
        sf::Text * text= new sf::Text("+200",font,28);
        text->setFillColor(sf::Color::Yellow);
        text->setPosition(coins[1].getPosition());
        _window.draw(*text);
    }
}

void Bonus::set_conditions_and_values()
{
    this->touched_first = false;
    this->touched_second = false;
    this->first_bonus_added = false;
    this->second_bonus_added = false;
    this->bonus_value = 0;
}

void Bonus::erase_vector()
{
    coins.erase(coins.begin(),coins.end());
}


void Bonus::add_bonus()
{
    this->bonus_value += 200;
}

int Bonus::get_bonus()
{
    return this->bonus_value;
}

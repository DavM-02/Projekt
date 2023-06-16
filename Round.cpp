#include "Round.h"
#include "PlayerObject.h"

Round::Round(int which_level)
{
    add_rounds();

    sf::Texture* texture = new sf::Texture();
    texture = rounds[which_level];
    this->actual_level = new sf::RectangleShape(sf::Vector2f(600.0, 80.0));
    actual_level->setTexture(texture);
    actual_level->scale(sf::Vector2f(0.6, 0.6));
    actual_level->setFillColor(sf::Color(255,255,255,128));
}

void Round::add_rounds()
{
    sf::Texture* texturetmp = new sf::Texture();
    texturetmp->loadFromFile("1_round.png");
    rounds.emplace_back(texturetmp);
    texturetmp = new sf::Texture();
    texturetmp->loadFromFile("2_round.png");
    rounds.emplace_back(texturetmp);
    texturetmp = new sf::Texture();
    texturetmp->loadFromFile("3_round.png");
    rounds.emplace_back(texturetmp);
    texturetmp = new sf::Texture();
    texturetmp->loadFromFile("4_round.png");
    rounds.emplace_back(texturetmp);
    texturetmp = new sf::Texture();
    texturetmp->loadFromFile("5_round.png");
    rounds.emplace_back(texturetmp);
}

sf::Texture* Round::get_some_texture(int& i)
{
    return this->rounds[i];
}

void Round::set_actual_texture(sf::Texture* _tex)
{
    this->actual_texture = _tex;
}

void Round::draw_buttons(sf::RenderWindow& _window, sf::View& view)
{


    sf::Texture* texture3 = new sf::Texture();
    texture3->loadFromFile("graj_dalej.png");
    sf::RectangleShape* graj_dalej = new sf::RectangleShape(sf::Vector2f(519.0, 52.0));
    graj_dalej->setTexture(texture3);
    graj_dalej->setPosition(sf::Vector2f(190.0, view.getCenter().y));
    _window.draw(*graj_dalej);

    sf::Texture* texture4 = new sf::Texture();
    texture4->loadFromFile("second_button.png");
    sf::RectangleShape* zakoncz = new sf::RectangleShape(sf::Vector2f(519.0, 52.0));
    zakoncz->setTexture(texture4);
    zakoncz->setPosition(sf::Vector2f(190.0, view.getCenter().y+150));
    _window.draw(*zakoncz);
    if(first_button_coordinates == sf::Vector2f(0.0,0.0) && second_button_coordinates == sf::Vector2f(0.0,0.0))
    {
        first_button_coordinates = graj_dalej->getPosition();
        second_button_coordinates = zakoncz->getPosition();
    }
}

sf::Vector2f Round::get_coordinates(int n)
{
    if(n == 0)
    {
        return this->first_button_coordinates;
    }
    else if(n == 1)
    {
        return this->second_button_coordinates;
    }
}

void Round::draw_round(sf::RenderWindow& _window, sf::Vector2f pos)
{
    actual_level->setPosition(pos);
    _window.draw(*actual_level);
}

sf::Text Round::get_points_text(PlayerObject* player,const sf::Vector2f& text_coords,sf::Font& font)
{
    if (!font.loadFromFile("Minecraft.ttf"))
    {
        throw("Missing font file!");
    }
    sf::Text *points_text=new sf::Text("Punkty: " + std::to_string(player->get_PointsNumber()),font,40);
    points_text->setFillColor(sf::Color::Green);
    points_text->setPosition(text_coords);
    return *points_text;
}

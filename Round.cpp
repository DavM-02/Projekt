
#include "Round.h"

Round::Round(int which_level, sf::RenderWindow& _window, sf::Vector2f pos)
{
    add_rounds();

    sf::Texture* texture = new sf::Texture();
    texture = rounds[which_level];
    sf::RectangleShape* _texture = new sf::RectangleShape(sf::Vector2f(600.0, 80.0));
    _texture->setTexture(texture);
    _texture->scale(sf::Vector2f(0.6, 0.6));
    _texture->setPosition(pos);
    _texture->setFillColor(sf::Color(255,255,255,128));
    _window.draw(*_texture);
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

sf::Texture* Round::get_some_texture(int i)
{
    return this->rounds[i];
}

void Round::set_actual_texture(sf::Texture* _tex)
{
    this->actual_texture = _tex;
}

void Round::draw_battons(sf::RenderWindow& _window, sf::View view)
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
}

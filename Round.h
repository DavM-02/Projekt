#pragma once
#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "PlayerObject.h"
class Round
{
    int _level;
    std::vector<sf::Texture*>rounds;
    sf::Vector2f first_button_coordinates = sf::Vector2f(1.0,1.0);
    sf::Vector2f second_button_coordinates = sf::Vector2f(1.0,1.0); //wspolrzedne przyciskow graj dalej i zakoncz po ukonczeniu kazdej z rund
    sf::Texture* actual_texture;
    sf::RectangleShape* actual_level;
public:
    Round(int which_level);
    void add_rounds();
    sf::Texture* get_some_texture(int& i);
    void set_actual_texture(sf::Texture* _tex);
    void draw_buttons(sf::RenderWindow& _window, sf::View& view);
    void draw_round(sf::RenderWindow& _window, const sf::Vector2f& pos);
    sf::Vector2f get_coordinates(int n);
    sf::Text get_text(PlayerObject* player,const sf::Vector2f& text_coords,sf::Font& font);
    sf::Text get_text(const std::vector<int>& points, const sf::Vector2f& text_coords, sf::Font& font);
};


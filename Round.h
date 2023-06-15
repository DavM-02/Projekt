#pragma once
#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



class Round
{
    int _level;
    std::vector<sf::Texture*>rounds;
    sf::Texture* actual_texture;
public:
    Round(int which_level, sf::RenderWindow& _window, sf::Vector2f pos);
    void add_rounds();
    sf::Texture* get_some_texture(int i);
    void set_actual_texture(sf::Texture* _tex);
    void draw_battons(sf::RenderWindow& _window, sf::View view);

};


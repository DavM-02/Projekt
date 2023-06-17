#pragma once
#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Menu
{
    sf::Texture* main_texture;
    sf::Sprite* _texture;
    std::vector<sf::Texture*>_other_textures;
    std::vector<sf::RectangleShape>positoned_textures;
public:
    Menu(const std::string& _texture_file);
    sf::Sprite* get_main_texture();
    void set_textures();
    std::vector<sf::RectangleShape> get_positoned_textures();
    void draw_initial_textures(sf::RenderWindow& _window);
};

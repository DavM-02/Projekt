#include "Menu.h"

Menu::Menu(std::string _texture_file)
{
    main_texture = new sf::Texture();
    if(!main_texture->loadFromFile(_texture_file))
    {
        throw("Missing texture file!");
    }
    this->_texture = new sf::Sprite(*main_texture);
    sf::Texture* texture_tmp = new sf::Texture();
    if(!texture_tmp->loadFromFile("first_button.png"))
    {
        throw("Missing texture file!");
    }
    else
    {
        _other_textures.emplace_back(texture_tmp);
    }
    texture_tmp = new sf::Texture();
    if(!texture_tmp->loadFromFile("second_button.png"))
    {
        throw("Missing texture file!");
    }
    else
    {
        _other_textures.emplace_back(texture_tmp);
    }
    set_textures();
}

void Menu::set_textures()
{
    float position_y = 400;
    for(int i=0; i<_other_textures.size(); i++)
    {
        sf::RectangleShape* _texture = new sf::RectangleShape(sf::Vector2f(519.0, 52.0));
        _texture->setTexture(_other_textures[i]);
        _texture->setPosition(sf::Vector2f(191.0, position_y));
        position_y += 150;
        positoned_textures.emplace_back(*_texture);
    }
}

sf::Sprite* Menu::get_main_texture()
{
    return this->_texture;
}

std::vector<sf::RectangleShape> Menu::get_positoned_textures()
{
    return positoned_textures;
}

std::vector<sf::Vector2f> Menu::get_buttons_positions()
{

}

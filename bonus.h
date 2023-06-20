#include<iostream>
#include <cstdlib>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Bonus
{
    sf::Texture* coin;
    std::vector<sf::RectangleShape>coins;
    bool touched_first = false;
    bool touched_second = false;
    bool first_bonus_added = false;
    bool second_bonus_added = false;
    int bonus_value = 0;
public:
    Bonus();
    void set_coin();
    void generate_coins(std::vector<float> coord_y);
    void draw_coins(sf::RenderWindow& _window, sf::FloatRect player_coord);
    void set_conditions_and_values();
    void erase_vector();
    void add_bonus();
    int get_bonus();
};
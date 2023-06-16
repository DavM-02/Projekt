#include "Game.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
Game::Game(sf::RenderWindow& _win,const std::string& _menu_texture) : window(_win)
{
    window.setFramerateLimit(120);
    sf::View _view(sf::FloatRect(0.f,0.f,900.f,900.f));
    window.setView(_view);
    view = _view;
    player = new PlayerObject({ 60.0,60.0 }, { 740.0,740.0 });
    menu = new Menu(_menu_texture);
    round = new Round(0);
}
sf::RenderWindow& Game::getWindow()
{
    return window;
}
void Game::gameLoop()
{
    while (window.isOpen())
    {
        menu->draw_initial_textures(window);
        imported_textures = menu->get_positoned_textures();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && enter_to_game) //Sprawdza czy zostala wscisnieta spacja
            {
                player->jump();
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(window).x >= imported_textures[0].getPosition().x && sf::Mouse::getPosition(window).x <= imported_textures[0].getPosition().x + 512 && sf::Mouse::getPosition(window).y >= imported_textures[0].getPosition().y && sf::Mouse::getPosition(window).y <= imported_textures[0].getPosition().y + 52 && !enter_to_game)
                {
                    enter_to_game = true; //gdy user kliknal przycisk "graj"
                    clock.restart();
                    platforms = create_platforms(); //Tworzymy wektor platform i zapisujemy tam platformy utworzone za pomoca funkcji
                    round = new Round(actual_level);  //tworzenie instancji klasy round
                }
                if (event.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(window).x >= imported_textures[1].getPosition().x && sf::Mouse::getPosition(window).x <= imported_textures[1].getPosition().x + 512 && sf::Mouse::getPosition(window).y >= imported_textures[1].getPosition().y && sf::Mouse::getPosition(window).y <= imported_textures[1].getPosition().y + 52 && !enter_to_game && !is_new_round)
                {
                    window.close();
                }
                if (event.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(window).x >= 190.0 && sf::Mouse::getPosition(window).x <= 709.0 && (sf::Mouse::getPosition(window).y + view.getCenter().y - 450) >= view.getCenter().y && (sf::Mouse::getPosition(window).y + view.getCenter().y - 450) <= view.getCenter().y + 52 && is_new_round && !enter_to_game && actual_level < 4)
                {
                    player->setPosition(sf::Vector2f(740.0,740.0));
                    enter_to_game = true;
                    is_new_round = false;
                    clock.restart();
                    platforms = create_platforms();
                    actual_level++;
                    round = new Round(actual_level);  //tworzenie instancji klasy round
                }
                if (event.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(window).x >= 190.0 && sf::Mouse::getPosition(window).x <= 709.0 && (sf::Mouse::getPosition(window).y + view.getCenter().y - 450) >= view.getCenter().y + 150 && (sf::Mouse::getPosition(window).y + view.getCenter().y - 450) <= view.getCenter().y + 202 && is_new_round && !enter_to_game && actual_level < 4)
                {
                    window.close();
                }
            }
        }
        if(enter_to_game)
        {
            new_round();
        }
        if(is_new_round)
        {
            enter_to_game = false;
            window.clear(sf::Color::Black);
            round_end();
        }

        if(end_of_the_game)
        {
            window.clear(sf::Color::Black);
            enter_to_game = false;
            is_new_round = false;
            end_of_game();
        }
        window.display();
    }
}
void Game::move_window()
{
    if(view.getCenter().y != player->getPosition().y+30)
    {
        view.move(sf::Vector2f{0,player->getPosition().y+30-view.getCenter().y}); //przesuwanie ekranu w pionie w zaleznosci od polozenia srodka widoku
    }
    window.setView(view);
    round->draw_round(window, sf::Vector2f(-45.0, view.getCenter().y-440)); //rysowanie numeru rundy
}
void Game::collision(const float& elapsed)
{
    for (int i = 0; i < platforms.size(); i++)
    {
        if (player->getGlobalBounds().intersects(platforms[i]->getGlobalBounds()))
        {
            float player_top = player->getGlobalBounds().top; //Górna wspólrzedna gracza
            float player_bot = player->getGlobalBounds().top + player->getGlobalBounds().height; //Dolna wspólrzedna gracza
            float player_left = player->getGlobalBounds().left; //Lewa wspólrzedna gracza
            float player_right = player->getGlobalBounds().left + player->getGlobalBounds().width; // Prawa wspólrzedna gracza
            float platform_top = platforms[i]->getGlobalBounds().top; //Górna wspólrzedna platformy
            float platform_bot = platforms[i]->getGlobalBounds().top + platforms[i]->getGlobalBounds().height; // Dolna wspólrzedna platformy
            float platform_left = platforms[i]->getGlobalBounds().left; //Lewa wspólrzêdna platformy
            float platform_right = platforms[i]->getGlobalBounds().left + platforms[i]->getGlobalBounds().width; //Prawa wspólrzedna platformy;

            if (player_bot > platform_top && player_top < platform_top) //Kolizja od góry
            {
                if (player_right > platform_left + 5 && player_left < platform_right - 5)
                {
                    player->setPosition(player->getPosition().x, platforms[i]->getGlobalBounds().top - player->getGlobalBounds().height);
                    player->setOnGround(true);
                    player->set_velocityY(0);
                    if (platforms[i]->getMovingState())
                    {
                        player->move({ platforms[i]->get_velocity().x * elapsed,0.0 }); // Jeśli gracz stoi na ruchomej platformie, przesuń go o wartość prędkości platformy
                    }
                    if (i == platforms.size() - 1)
                    {
                        if (actual_level == 4)
                            end_of_the_game = true; //kiedy ukonczymy ostatni poziom - gra sie konczy
                        if (actual_level < 4)
                            is_new_round = true; //kiedy ukonczymy dany poziom;
                        player->addPoints((1 / round_clock.restart().asSeconds()) * 10000);
                    }
                }
                else
                {
                    if (player_left < platform_right && player_left > platform_right - 4) //Kolizja od prawej
                    {
                        player->setPosition(platform_right, player->getPosition().y);
                        player->set_velocityX(0);
                    }
                    else if (player_right > platform_left && player_right < platform_left + 4) //Kolizja od lewej
                    {
                        player->setPosition(platform_left - player->getGlobalBounds().width, player->getPosition().y);
                        player->set_velocityX(0);
                    }
                }
            }
            else if (player_top < platform_bot && player_left < platform_right && player_right > platform_left) //Kolizja od dolu
            {
                player->setPosition(player->getPosition().x, platform_bot);
                player->set_velocityY(0);
            }
            else if (player_left < platform_right && player_right>platform_right && player_bot < platform_top) //Kolizja od prawej
            {
                player->setPosition(platform_right, player->getPosition().y);
                player->set_velocityX(0);
            }
            else if (player_right > platform_left && player_left < platform_right && player_bot < platform_top) //Kolizja od lewej
            {
                player->setPosition(platform_left - player->getGlobalBounds().width, player->getPosition().y);
                player->set_velocityX(0);
            }
        }
    }
}
void Game::window_collision()
{
    if (player->getPosition().x <= 0) //Kolizja z lewa sciana okna
    {
        player->setPosition(0, player->getPosition().y);
    }
    if (player->getPosition().x + player->getGlobalBounds().width >= window.getSize().x) //Kolizja z prawa sciana okna
    {
        player->setPosition(window.getSize().x - player->getGlobalBounds().width, player->getPosition().y);
    }
    if (player->getPosition().y + player->getGlobalBounds().height >= window.getSize().y) //Kolizja z dolna sciana okna
    {
        player->setPosition(player->getPosition().x, window.getSize().y - player->getGlobalBounds().height);
        player->setOnGround(true);
    }
    for (int i = 1; i < platforms.size(); i++)
    {
        if (platforms[i]->getPosition().x + platforms[i]->getGlobalBounds().width >= window.getSize().x) //Kolizja platformy od prawej strony
        {
            platforms[i]->set_velocityX(platforms[i]->get_velocity().x * (-1));
            platforms[i]->setPosition(window.getSize().x - platforms[i]->getGlobalBounds().width, platforms[i]->getPosition().y);
        }
        else if (platforms[i]->getPosition().x <= 0) //Kolizja platformy od lewej strony
        {
            platforms[i]->set_velocityX(platforms[i]->get_velocity().x * (-1));
            platforms[i]->setPosition(0, platforms[i]->getPosition().y);
        }
    }
}

std::vector<PlatformObject*> Game::create_platforms()
{
    float position_x = 0;
    float position_y = 600;
    srand((unsigned)time(0));
    int acc = 0;
    platforms.clear();
    PlatformObject* base_platform = new PlatformObject({0.0,800.0}, { 900.0, 18.0 },false);
    base_platform->setFillColor(sf::Color::Red);
    platforms.emplace_back(base_platform);

    while (position_y >= -1000)
    {
        PlatformObject* platform = new PlatformObject({ 130.0,18.0 },true); //Zamiast platformy jako RectangleShape robimy platformy jako PlatformObject
        float tmp = rand() % 780;
        if (acc >= 1) //aby w miare rozsadnych odleglosciach sie te platformy respily xD
        {
            if (((std::abs(tmp - position_x)) >= 0) && ((std::abs(tmp - position_x)) <= 130))
            {
                if ((tmp - position_x) >= 0)
                {
                    position_x = tmp + 120.f;
                }
                else if ((tmp - position_x) < 0)
                {
                    position_x = tmp - 120.f;
                }
            }
            else if ((std::abs(tmp - position_x)) > 360)
            {
                if ((tmp - position_x) >= 0)
                {
                    position_x = tmp - 180.f;
                }
                else if ((tmp - position_x) < 0)
                {
                    position_x = tmp + 180.f;
                }
            }
            else if ((std::abs(tmp - position_x)) > 130)
            {
                position_x = tmp;
            }
        }
        else
        {
            position_x = tmp;
        }                                                                // dotad
        platform->setPosition(position_x, position_y);
        platform->setFillColor(sf::Color::Magenta);
        position_y = position_y - 220;
        platforms.emplace_back(platform);
        acc++;
    }
    return platforms;
}

void Game::new_round()
{
    //Sprawdza czy przyciski lewo/prawo sa wcisniete (jest róznica miêdzy tymi ifami a ifem ze spacji)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player->set_velocityX(400);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player->set_velocityX(-400);
    else
        player->set_velocityX(0);

    float elapsed = clock.restart().asSeconds(); //Czas pomiedzy wygenerowanymi klatkami
    //Ruch gracza i sprawdzanie kolizji z oknem i platformami
    player->animate(elapsed);
    window_collision();
    collision(elapsed);
    window.clear(sf::Color::Black);
    for (int i = 0; i < platforms.size(); i++)
    {
        window.draw(*platforms[i]);
        platforms[i]->animate(elapsed);
    }
    window.draw(*player);
    move_window();
}

void Game::round_end()
{
    sf::Texture* texture1 = new sf::Texture();
    texture1->loadFromFile("_ukonczona.png");
    sf::RectangleShape* end_of_round = new sf::RectangleShape(sf::Vector2f(900.0, 900.0));
    end_of_round->setTexture(texture1);
    end_of_round->setPosition(sf::Vector2f(0.0,view.getCenter().y-450.0));
    window.draw(*end_of_round);

    sf::Texture* texture2 = new sf::Texture();
    texture2 = round->get_some_texture(actual_level);
    sf::RectangleShape* actual_round = new sf::RectangleShape(sf::Vector2f(600.0, 80.0));
    actual_round->setTexture(texture2);
    actual_round->scale(sf::Vector2f(1.3, 1.3));
    actual_round->setPosition(sf::Vector2f(80.0, view.getCenter().y-350.0));
    window.draw(*actual_round);
    round->draw_buttons(window,view);
    window.draw(round->get_points_text(player, window.mapPixelToCoords({ 10,15 }), text_font)); 
}

void Game::end_of_game()
{
    sf::Texture* texture1 = new sf::Texture();
    texture1->loadFromFile("end_of_game.png");
    sf::RectangleShape* end_of_round = new sf::RectangleShape(sf::Vector2f(900.0, 900.0));
    end_of_round->setTexture(texture1);
    end_of_round->setPosition(sf::Vector2f(0.0,view.getCenter().y-450.0));
    //Zapis wyniku do pliku tekstowego
    if (!file_updated)
    {
        std::ofstream file;
        auto now = std::chrono::zoned_time{ std::chrono::current_zone(), floor<std::chrono::seconds>(std::chrono::system_clock::now()) }.get_local_time();
        auto ld = floor<std::chrono::days>(now);
        std::chrono::year_month_day ymd{ ld };
        std::chrono::hh_mm_ss hms{ now - ld };
        file.open("wyniki.txt", std::ios_base::app);
        if (file.is_open())
        {
            file << player->get_PointsNumber() << ' ' << ymd << ' ' << hms << std::endl;
        }
        file_updated = true;
    }

    window.draw(*end_of_round);
    window.draw(round->get_points_text(player, window.mapPixelToCoords({ 10,15 }), text_font));
}

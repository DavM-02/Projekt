#include "Game.h"
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
Game::Game(sf::RenderWindow& _win, std::string _menu_texture) : window(_win)
{
    window.setFramerateLimit(120);
    sf::View _view(sf::FloatRect(0.f,0.f,900.f,900.f));
    window.setView(_view);
    view = _view;
    player = new PlayerObject({ 60.0,60.0 }, { 740.0,740.0 });
    platforms = create_platforms(); //Tworzymy wektor platform i zapisujemy tam platformy utworzone za pomoca funkcji
    this->menu = new Menu(_menu_texture);
}
sf::RenderWindow& Game::getWindow()
{
    return window;
}
sf::Vector2f Game::get_gravity()
{
    return gravity;
}
void Game::gameLoop()
{
    while (window.isOpen())
    {
        //std::cout << player->getPosition().y << std::endl;
        window.draw(*(menu->get_main_texture()));
        this->imported_textures = this->menu->get_positoned_textures();
        for(int i = 0; i < imported_textures.size(); i++)
        {
            window.draw(imported_textures[i]); // rysowanie przyciskow graj i zakoncz
        }
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
                    if (event.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(window).x >= imported_textures[0].getPosition().x && sf::Mouse::getPosition(window).x <= imported_textures[0].getPosition().x+512 && sf::Mouse::getPosition(window).y >= imported_textures[0].getPosition().y && sf::Mouse::getPosition(window).y <= imported_textures[0].getPosition().y+52)
                    {
                        enter_to_game = true; //gdy user kliknal przycisk "graj"
                        clock.restart();
                    }
                    if (event.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(window).x >= imported_textures[1].getPosition().x && sf::Mouse::getPosition(window).x <= imported_textures[1].getPosition().x+512 && sf::Mouse::getPosition(window).y >= imported_textures[1].getPosition().y && sf::Mouse::getPosition(window).y <= imported_textures[1].getPosition().y+52)
                    {
                        window.close();
                    }
            }
        }

        if(enter_to_game)
        {
            //Sprawdza czy przyciski lewo/prawo sa wcisniete (jest róznica miêdzy tymi ifami a ifem ze spacji)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    player->set_velocityX(400);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    player->set_velocityX(-400);
            else
                    player->set_velocityX(0);


            float elapsed = clock.restart().asSeconds(); //Czas pomiedzy wygenerowanymi klatkami
            std::cout << elapsed << std::endl;
            //Ruch gracza i sprawdzanie kolizji z oknem i platformami
            player->animate(elapsed,gravity);
            window_collision();
            collision();
            move_window();
            window.clear(sf::Color::Black);
            for (int i = 0; i < platforms.size(); i++)
            {
                window.draw(*platforms[i]);
            }
            window.draw(*player);
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
}
void Game::collision()
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
                    //std::cout << "gora" << std::endl;
                }
                else
                {
                    if (player_left < platform_right && player_left > platform_right - 4)
                    {
                        std::cout << "prawo" << std::endl;
                        player->setPosition(platform_right, player->getPosition().y);
                        player->set_velocityX(0);
                    }
                    else if (player_right > platform_left && player_right < platform_left + 4)
                    {
                        std::cout << "lewo" << std::endl;
                        player->setPosition(platform_left - player->getGlobalBounds().width, player->getPosition().y);
                        player->set_velocityX(0);
                    }
                }
            }
            else if (player_top < platform_bot && player_left < platform_right && player_right > platform_left) //Kolizja od dolu
            {
                std::cout << "dol" << std::endl;
                player->setPosition(player->getPosition().x, platform_bot);
                player->set_velocityY(0);
            }
            else if (player_left < platform_right && player_right>platform_right && player_bot < platform_top)
            {
                std::cout << "prawo" << std::endl;
                player->setPosition(platform_right, player->getPosition().y);
                player->set_velocityX(0);
            }
            else if (player_right > platform_left && player_left < platform_right && player_bot < platform_top)
            {
                std::cout << "lewo" << std::endl;
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
}

std::vector<PlatformObject*> Game::create_platforms()
{
    float position_x = 0;
    float position_y = 600;
    srand((unsigned)time(0));
    int acc = 0;
    std::vector<PlatformObject*> platforms;
    PlatformObject* base_platform = new PlatformObject({ 800.0,18.0 });
    base_platform->setPosition(50.f, 800.f);
    base_platform->setFillColor(sf::Color::Red);
    platforms.emplace_back(base_platform);

    while (position_y >= -1000)
    {
        PlatformObject* platform = new PlatformObject({ 130.0,18.0 }); //Zamiast platformy jako RectangleShape robimy platformy jako PlatformObject
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

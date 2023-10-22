#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "NewMenu.h"
#include "Enemy.h"
#include <random>
#include <vector>
#include "PauseMenu.h"

enum GameState
{
    MENU, GAME, PAUSE, END
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(550, 800), "SFML Game",sf::Style::Close | sf::Style::Resize);
    NewMenu   menu(window.getSize().x, window.getSize().y);
    PauseMenu pause(window.getSize().x / 4.f, window.getSize().y / 2.f);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("Knight.png");

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Assets/Assets/Blue wizard/BlueWizard.png");

    Player player(&playerTexture, sf::Vector2u(4, 2), 0.3f, 100.0f);

    std::vector<Enemy> enemies;

    float deltaTime = 0.0f;
    sf::Clock clock;

    std::random_device rd;
    std::mt19937 gen(rd());

    //temporary
    float spawnEnemyX = (rand() % 460);
    sf::Vector2f position(spawnEnemyX, 0.0f);
    Enemy enemy(&enemyTexture, sf::Vector2u(2, 1), 0.5f, 50.0f, position);

    GameState state = MENU;
    while (window.isOpen())
    { 
        deltaTime = clock.restart().asSeconds();

        sf::Event evnt;
        if (state == MENU)
        {
            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::KeyReleased:
                    switch (evnt.key.code)
                    {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;

                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;

                    case sf::Keyboard::Return:
                        switch (menu.GetPressedItem())
                        {
                        case 0:
                            std::cout << "Fight button" << std::endl;
                            state = GAME;
                            break;
                        case 1:
                            std::cout << "Option button" << std::endl;
                            break;
                        case 2:
                            window.close();
                            break;
                        }
                    }

                    break;

                case sf::Event::Closed:
                    window.close();
                    break;
                }


            }
            /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                player.move(-0.1f, 0.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                player.move(0.1f, 0.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                player.move(0.0f, -0.1f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                player.move(0.0f, 0.1f);
            }*/

            /*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                player.setPosition((float)mousePos.x, (float)mousePos.y);
            }*/

            window.clear(sf::Color(67, 165, 220));
            menu.draw(window);
            window.display();
        }

        if (state == GAME)
        {
            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::KeyReleased:
                    switch (evnt.key.code)
                    {
                    case sf::Keyboard::Escape:
                        //switch (menu.GetPressedItem())***************************************
                        {
                        
                            std::cout << "Pause" << std::endl;
                            state = PAUSE;
                            break;
                        /*case 1:
                            std::cout << "Option button" << std::endl;
                            break;
                        case 2:
                            window.close();
                            break;*/
                        }
                    }

                    /*break;*/

                /*case sf::Event::Closed:
                    window.close();
                    break;*/
                }
            }          

            player.Update(deltaTime);
            enemy.Update(deltaTime);
            window.clear(sf::Color(150, 150, 150));
            player.Draw(window);
            enemy.Draw(window);
            window.display();

        }

        if (state == PAUSE)
        {
            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::KeyReleased:
                    switch (evnt.key.code)
                    {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;

                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;

                    case sf::Keyboard::Return:
                        switch (menu.GetPressedItem())
                        {
                        case 0:
                            std::cout << "Resume" << std::endl;
                            state = GAME;
                            break;
                        case 1:
                            state = MENU;
                            break;
                        }
                    }

                    break;

                case sf::Event::Closed:
                    window.close();
                    break;
                }

                window.clear(sf::Color(67, 165, 220, 50));
                pause.draw(window);
                window.display();
            }
        }
    }
        
    return 0;
}
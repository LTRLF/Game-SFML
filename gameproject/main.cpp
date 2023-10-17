#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "NewMenu.h"

enum GameState
{
    MENU, GAME
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game",sf::Style::Close | sf::Style::Resize);
    NewMenu menu(window.getSize().x, window.getSize().y);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("Knight.png");

    Player player(&playerTexture, sf::Vector2u(4, 2), 0.3f, 100.0f);

    float deltaTime = 0.0f;
    sf::Clock clock;

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

            window.clear();
            menu.draw(window);
            window.display();
        }

        if (state == GAME)
        {
            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }
            player.Update(deltaTime);
            window.clear(sf::Color(150, 150, 150));
            player.Draw(window);
            window.display();

        }
    }

    //test 1
        
    return 0;
}
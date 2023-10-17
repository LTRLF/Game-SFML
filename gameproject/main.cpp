#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "NewMenu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game",sf::Style::Close | sf::Style::Resize);
    NewMenu menu(window.getSize().x, window.getSize().y);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("Knight.png");

    Player player(&playerTexture, sf::Vector2u(4, 2), 0.3f, 100.0f);

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    { 
        deltaTime = clock.restart().asSeconds();

        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
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
            
        player.Update(deltaTime);

        window.clear(sf::Color(150, 150, 150));
        menu.draw(window);
        player.Draw(window);
        window.display();
    }

    return 0;
    //fcpp
}
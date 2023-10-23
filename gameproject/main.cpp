#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "NewMenu.h"
#include "Enemy.h"
#include <random>
#include <vector>
#include "PauseMenu.h"
#include "Logic.h"
#include "main.h"
using namespace sf;

enum GameState
{
    MENU, GAME, PAUSE, END
};

std::string KeyToString(sf::Keyboard::Key key) {
    switch (key) {
    case sf::Keyboard::Up:
        return "Up Arrow";
    case sf::Keyboard::Left:
        return "Left Arrow";
    case sf::Keyboard::Down:
        return "Down Arrow";
    case sf::Keyboard::Right:
        return "Right Arrow";
    default:
        return "Unknown";
    }
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow window(sf::VideoMode(550, 800), "SFML Game",sf::Style::Close);
    NewMenu   menu(window.getSize().x, window.getSize().y);
    PauseMenu pause(window.getSize().x / 4.f, window.getSize().y / 2.f);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("Assets/Assets/background.png");
    sf::RectangleShape background(sf::Vector2f(550, 800));
    background.setTexture(&backgroundTexture);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("Knight.png");

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Assets/Assets/Blue wizard/BlueWizard.png");

    sf::Font font;
    if (!font.loadFromFile("Next Bro.ttf"))
    {
        //handle error
    }
    //arrow graphics
    sf::Texture upTexture;
    upTexture.loadFromFile("Assets/Assets/Buttons/Pixel Up Buttons.png");
    sf::Texture downTexture;
    downTexture.loadFromFile("Assets/Assets/Buttons/Pixel Down Buttons.png");
    sf::Texture leftTexture;
    leftTexture.loadFromFile("Assets/Assets/Buttons/Pixel Left Buttons.png");
    sf::Texture rightTexture;
    rightTexture.loadFromFile("Assets/Assets/Buttons/Pixel Right Buttons.png");

    sf::RectangleShape shape;
    shape.setSize(Vector2f(64, 64));
    shape.setTexture(&upTexture);
    shape.setPosition(260.0f, 330.0f);

    Player player(&playerTexture, sf::Vector2u(4, 2), 0.3f, 100.0f);

    std::vector<Enemy> enemies;

    float deltaTime = 0.0f;
    sf::Clock clock;

    std::random_device rd;
    std::mt19937 gen(rd());

    //temporary
    float spawnEnemyX = (rand() % 460);
    sf::Vector2f position(spawnEnemyX, -1.0f);
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
            sf::Text keyText;
            keyText.setFont(font);
            keyText.setCharacterSize(24);
            keyText.setFillColor(sf::Color::White);
            keyText.setPosition(190.0f, 330.0f);

            sf::Keyboard::Key randomKey = static_cast<sf::Keyboard::Key>(sf::Keyboard::Left + rand() % 4);
            std::string keyString = KeyToString(randomKey);
            keyText.setString ("Press: ");

            while (window.isOpen()) {
                sf::Event evnt;
                while (window.pollEvent(evnt))
                {
                    if (evnt.type == sf::Event::Closed) {
                        window.close();
                    }

                    /*if (Logic.life() >= 0)
                    {*/
                    if (evnt.type == sf::Event::KeyPressed) {
                        if (evnt.key.code == randomKey) {
                            std::cout << "Correct Key Pressed!" << std::endl;
                            randomKey = static_cast<sf::Keyboard::Key>(sf::Keyboard::Left + rand() % 4);
                            keyString = KeyToString(randomKey);
                            keyText.setString("Press: ");
                        }
                        else {
                            std::cout << "Wrong Key Pressed!" << std::endl;
                        }
                    }

                    switch (evnt.type)
                    {
                    case sf::Event::KeyReleased:
                        switch (evnt.key.code)
                        {
                            case sf::Keyboard::Escape:
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
                    //}

                    /*else
                    {
                        state = END;
                    }*/

                    

                }

                if (randomKey == sf::Keyboard::Up) {
                    shape.setTexture(&upTexture);
                }
                else if (randomKey == sf::Keyboard::Down) {
                    shape.setTexture(&downTexture);
                }
                else if (randomKey == sf::Keyboard::Left) {
                    shape.setTexture(&leftTexture);
                }
                else if (randomKey == sf::Keyboard::Right) {
                    shape.setTexture(&rightTexture);
                }

                player.Update(deltaTime);
                enemy.Update(deltaTime);
                window.draw(background);
                player.Draw(window);
                enemy.Draw(window);
                window.draw(keyText);
                window.draw(shape);
                window.display();

            }
        }

        if (state == PAUSE)
        {
            //window.clear();
            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::KeyReleased:
                    switch (evnt.key.code)
                    {
                    case sf::Keyboard::Up:
                        pause.MoveUp();
                        break;

                    case sf::Keyboard::Down:
                        pause.MoveDown();
                        break;

                    case sf::Keyboard::Return:
                        switch (pause.GetPressedItem())
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

                //window.clear(/*sf::Color(100, 150, 150, 50)*/);
                player.Draw(window);
                enemy.Draw(window);
                pause.draw(window);
                window.display();
            }
        }
    }
        
    return 0;
}
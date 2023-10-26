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
#include <sstream>
using namespace sf;
using namespace std;

enum GameState
{
    MENU, GAME, PAUSE, END, READY
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

    sf::RenderWindow window(sf::VideoMode(550, 800), "Press[!] No Wait", sf::Style::Close);
    NewMenu   menu(window.getSize().x, window.getSize().y);
    PauseMenu pause(window.getSize().x / 4.f, window.getSize().y / 2.f);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("Assets/Assets/background.png");
    sf::RectangleShape background(sf::Vector2f(550, 800));
    background.setTexture(&backgroundTexture);

    sf::Texture skyTexture;
    skyTexture.loadFromFile("Assets/Assets/sky.jpg");
    sf::RectangleShape sky(sf::Vector2f(550, 800));
    sky.setTexture(&skyTexture);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("Knight.png");

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Assets/Assets/Blue wizard/BlueWizard.png");

    int score = 0;


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
    std::string stringUsername;

    std::vector<Enemy> enemies;

    float deltaTime = 0.0f;
    sf::Clock clock;

    std::random_device rd;
    std::mt19937 gen(rd());

    //temporary
    float spawnEnemyX = (rand() % 460);
    float speed = 40;
    sf::Vector2f position(spawnEnemyX, -100.0f);
    Enemy enemy(&enemyTexture, sf::Vector2u(2, 1), 0.5f, speed, position);

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
                            score = 0;
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

        if (state == READY) {
            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;

                    if (evnt.type == sf::Event::TextEntered) {
                        if (evnt.text.unicode == sf::Keyboard::BackSpace) {
                            stringUsername = stringUsername.substr(0, stringUsername.size() - 1);
                        }
                        else if (evnt.text.unicode != sf::Keyboard::Return && evnt.text.unicode != sf::Keyboard::Escape && stringUsername.size() < 12) {
                            stringUsername += evnt.text.unicode;
                        }
                    }
                }
            }
            window.clear(sf::Color(67, 165, 220));
            window.draw(sky);
            window.display();
        }

        if (state == GAME || state == PAUSE)
        {
            sf::Text keyText;
            keyText.setFont(font);
            keyText.setCharacterSize(24);
            keyText.setFillColor(sf::Color::White);
            keyText.setPosition(190.0f, 330.0f);

            sf::Keyboard::Key randomKey = static_cast<sf::Keyboard::Key>(sf::Keyboard::Left + rand() % 4);
            std::string keyString = KeyToString(randomKey);
            keyText.setString("Press: ");

            //score
            Font font;
            font.loadFromFile("Next Bro.ttf");
            int curscore = 0;
            Text score;
            score.setFont(font);
            score.setCharacterSize(24);
            score.setString("Score: " + std::to_string(curscore));

            //lives
            int lives = 3;
            Text life;
            life.setFont(font);
            life.setCharacterSize(24);
            life.setString("Lives: " + std::to_string(lives));
            life.setPosition(sf::Vector2f(0, 30));

            //enemyhp
            int enemyhp = 3;

            while (state == GAME || state == PAUSE)
            {
                sf::Event evnt;
                while (window.pollEvent(evnt))
                {
                    if (evnt.type == sf::Event::Closed) {
                        window.close();
                    }

                    if (evnt.type == sf::Event::KeyPressed && evnt.key.code >= 71 && evnt.key.code <= 74 && state == GAME) {
                        if (evnt.key.code == randomKey) {
                            curscore += 5;
                            enemyhp -= 1;
                            score.setString("Score: " + std::to_string(curscore));
                            std::cout << "Correct Key Pressed!" << std::endl;
                            randomKey = static_cast<sf::Keyboard::Key>(sf::Keyboard::Left + rand() % 4);
                            keyString = KeyToString(randomKey);
                            keyText.setString("Press: ");
                        }
                        else {
                            randomKey = static_cast<sf::Keyboard::Key>(sf::Keyboard::Left + rand() % 4);
                            std::cout << "Wrong Key Pressed!" << std::endl;
                            enemyhp = 3;
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

                if (enemy.getBody().getPosition().y >= player.getBody().getPosition().y) {
                    lives -= 1;
                    life.setString("Lives: " + std::to_string(lives));

                    float spawnEnemyX = (rand() % 460);
                    float speed = 40;
                    sf::Vector2f position(spawnEnemyX, -100.0f);
                    enemy.getBody().setPosition(position);
                    enemyhp = 3;
                }

                if (enemyhp == 0) {
                    float spawnEnemyX = (rand() % 460);
                    speed = 40;
                    sf::Vector2f position(spawnEnemyX, -100.0f);
                    enemy.getBody().setPosition(position);
                    enemyhp = 3;
                }

                if (lives == 0) {
                    state = END;
                }

                if (state == PAUSE)
                {


                    switch (evnt.type)
                    {
                    case sf::Event::KeyReleased:
                        switch (evnt.key.code)
                        {
                        case sf::Keyboard::Up:
                            pause.MoveUp();
                            continue;
                        case sf::Keyboard::Down:
                            pause.MoveDown();
                            continue;

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

                    window.clear();
                    window.draw(background);
                    window.draw(score);
                    pause.draw(window);
                    window.display();
                    continue;
                }

                player.Update(deltaTime);
                enemy.Update(deltaTime);
                window.draw(background);
                player.Draw(window);
                enemy.Draw(window);
                window.draw(keyText);
                window.draw(score);
                window.draw(life);
                window.draw(shape);
                window.display();

            }

        }

    }

    return 0;
}
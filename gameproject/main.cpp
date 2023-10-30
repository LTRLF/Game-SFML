#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "NewMenu.h"
#include "Enemy.h"
#include <random>
#include <vector>
#include "PauseMenu.h"
#include "main.h"
#include "EndGame.h"
#include <sstream>
#include <fstream>
using namespace sf;
using namespace std;

enum GameState
{
    MENU, GAME, PAUSE, END, READY, SCOREBOARD
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

void saveScore(std::string name, int score)
{
    std::ofstream file;
    file.open("Assets/Assets/scoreboard.txt", std::ios::app);
    file << name << " " << score << std::endl;
    file.close();
}

void printScore(sf::Text* ScoreTop)
{
    std::ifstream file;
    file.open("Assets/Assets/scoreboard.txt");
    std::string line;
    std::vector<std::pair<std::string, int>> scores;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int score;
        iss >> name >> score;
        scores.push_back(std::make_pair(name, score));
    }
    file.close();
    std::sort(scores.begin(), scores.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
        });

    for (int i = 0; i < 5 && i < scores.size(); i++) {
        ScoreTop[i].setString(std::to_string(i + 1) + " : " + std::to_string(scores[i].second) + " " + scores[i].first);
    }

}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    //render window
    sf::RenderWindow window(sf::VideoMode(550, 800), "Press Next[!] Wait", sf::Style::Close);
    NewMenu   menu(window.getSize().x, window.getSize().y);
    PauseMenu pause(window.getSize().x / 4.f, window.getSize().y / 2.f);
    EndGame   end(window.getSize().x / 4.f, window.getSize().y / 2.f);

    //game background
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("Assets/Assets/background.png");
    sf::RectangleShape background(sf::Vector2f(550, 800));
    background.setTexture(&backgroundTexture);

    //READY background
    sf::Texture skyTexture;
    skyTexture.loadFromFile("Assets/Assets/sky.jpg");
    sf::RectangleShape sky(sf::Vector2f(550, 800));
    sky.setTexture(&skyTexture);

    //MENU background
    sf::Texture menuBGTexture;
    menuBGTexture.loadFromFile("Assets/Assets/MenuBg.png");
    sf::RectangleShape menuBG(sf::Vector2f(550, 800));
    menuBG.setTexture(&menuBGTexture);

    //player sprite 
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Assets/Assets/Knight.png");

    //enemy sprite
    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Assets/Assets/Blue wizard/BlueWizard.png");

    int curscore;
    std::string stringUsername;

    //import font
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

    //square to put the arrow graphics in
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

    //enemy
    float spawnEnemyX = (rand() % 460);
    float speed = 400;
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
                            curscore = 0;
                            state = READY;
                            break;
                        case 1:
                            std::cout << "ScoreBoard button" << std::endl;
                            state = SCOREBOARD;
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
            window.draw(menuBG);
            menu.draw(window);
            window.display();
        }

        if (state == READY) {
            sf::Text name;
            name.setFont(font);
            name.setCharacterSize(50);
            name.setFillColor(sf::Color(35, 35, 35));
            name.setPosition(80, 210);
            name.setString("Perhaps thee could \ntell I thy name?");

            sf::Text user;
            user.setFont(font);
            user.setCharacterSize(40);
            user.setFillColor(sf::Color(35, 35, 35));
            user.setPosition(280, 380);

            stringUsername.clear();

            while (state == READY)
            {
                while (window.pollEvent(evnt))
                {
                    switch (evnt.type)
                    {
                    case sf::Event::Closed:
                        window.close();
                        break;

                    case sf::Event::TextEntered:
                        if (evnt.text.unicode < 128 && evnt.text.unicode > 32)
                        {
                            stringUsername += evnt.text.unicode;
                            user.setString(stringUsername);
                            user.setOrigin(user.getGlobalBounds().width / 2, user.getGlobalBounds().height / 2);
                        }
                        else if (evnt.text.unicode == 8 && !stringUsername.empty())
                        {
                            stringUsername.pop_back();
                            user.setString(stringUsername);
                            user.setOrigin(user.getGlobalBounds().width / 2, user.getGlobalBounds().height / 2);
                        }
                        else if (evnt.text.unicode == 13 && !stringUsername.empty())
                        {
                            state = GAME;
                        }
                        else if (evnt.text.unicode == 27)
                        {
                            state = MENU;
                        }
                        break;
                    }
                }
                window.clear();
                window.draw(sky);
                window.draw(name);
                window.draw(user);
                window.display();
            }
        }

        if (state == GAME || state == PAUSE)
        {
            sf::Text keyText;
            keyText.setFont(font);
            keyText.setCharacterSize(24);
            keyText.setFillColor(sf::Color::White);
            keyText.setPosition(190.0f, 330.0f);

            //random key
            sf::Keyboard::Key randomKey = static_cast<sf::Keyboard::Key>(sf::Keyboard::Left + rand() % 4);
            std::string keyString = KeyToString(randomKey);
            keyText.setString("Press: ");

            //score
            Font font;
            font.loadFromFile("Next Bro.ttf");
            curscore = 0;
            Text txtscore;
            txtscore.setFont(font);
            txtscore.setCharacterSize(24);
            txtscore.setString("Score: " + std::to_string(curscore));

            //lives
            int lives = 3;
            Text life;
            life.setFont(font);
            life.setCharacterSize(24);
            life.setString("Lives: " + std::to_string(lives));
            life.setPosition(sf::Vector2f(0, 30));

            //enemyhp
            int enemyhp = 3;

            float spawnEnemyX = (rand() % 460);
            speed = 40;
            sf::Vector2f position(spawnEnemyX, -100.0f);
            enemy.getBody().setPosition(position);

            while (state == GAME || state == PAUSE)
            {
                sf::Event evnt;
                while (window.pollEvent(evnt))
                {
                    if (evnt.type == sf::Event::Closed) {
                        window.close();
                    }

                    //correct key pressed
                    if (evnt.type == sf::Event::KeyPressed && evnt.key.code >= 71 && evnt.key.code <= 74 && state == GAME) {
                        if (evnt.key.code == randomKey) {
                            curscore += 5;
                            enemyhp -= 1;
                            txtscore.setString("Score: " + std::to_string(curscore));
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

                    }

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
                    sf::Vector2f position(spawnEnemyX, -100.0f);
                    enemy.getBody().setPosition(position);
                    enemyhp = 3;
                }

                if (enemyhp == 0) {
                    float spawnEnemyX = (rand() % 460);
                    enemy.speed += 2;
                    sf::Vector2f position(spawnEnemyX, -100.0f);
                    enemy.getBody().setPosition(position);
                    enemyhp = 3;
                }

                if (lives == 0) {
                    saveScore(stringUsername, curscore);
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
                            evnt.key.code = sf::Keyboard::Unknown;
                            break;
                        case sf::Keyboard::Down:
                            pause.MoveDown();
                            evnt.key.code = sf::Keyboard::Unknown;
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

                    window.clear();
                    window.draw(background);
                    window.draw(txtscore);
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
                window.draw(txtscore);
                window.draw(life);
                window.draw(shape);
                window.display();

            }

        }

        if (state == END)
        {
            //score display
            Font font;
            font.loadFromFile("Next Bro.ttf");
            Text txtscore;
            txtscore.setFont(font);
            txtscore.setCharacterSize(30);
            txtscore.setPosition(230.0f, 275.0f);
            txtscore.setString("Score: " + std::to_string(curscore));

            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::KeyReleased:
                    switch (evnt.key.code)
                    {
                    case sf::Keyboard::Up:
                        end.MoveUp();
                        evnt.key.code = sf::Keyboard::Unknown;
                        break;
                    case sf::Keyboard::Down:
                        end.MoveDown();
                        evnt.key.code = sf::Keyboard::Unknown;
                        break;

                    case sf::Keyboard::Return:
                        switch (end.GetPressedItem())
                        {
                        case 0:
                            std::cout << "Play Again" << std::endl;
                            state = GAME;
                            break;
                        case 1:
                            //scoreboard
                        case 2:
                            state = MENU;
                            break;
                        }
                    }

                    break;

                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }
            window.clear();
            window.draw(background);
            end.draw(window);
            window.draw(txtscore);
            window.display();
            continue;
        }

        if (state == SCOREBOARD)
        {
            sf::RectangleShape scorebg;
            scorebg.setSize(sf::Vector2f(400.0f, 400.0f));
            scorebg.setFillColor(sf::Color(150, 150, 150, 200));
            scorebg.setPosition(75.0f, 215.0f);

            Text scoretitle;
            scoretitle.setFont(font);
            scoretitle.setCharacterSize(50);
            scoretitle.setPosition(160.0f, 250.0f);
            scoretitle.setString("Scoreboard");

            sf::Text ScoreTop[5];
            printScore(ScoreTop);

            for (int i = 0; i < 5; i++) {
                ScoreTop[i].setFont(font);
                ScoreTop[i].setCharacterSize(35);
                ScoreTop[i].setFillColor(sf::Color::White);
                ScoreTop[i].setPosition(120, 340 + (i * 50));
            }

            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (evnt.key.code == sf::Keyboard::Escape)
                    {
                        state = MENU;
                    }
                }
            }
            window.clear();
            window.draw(sky);
            window.draw(scorebg);
            window.draw(scoretitle);

            for (int i = 0; i < 5; i++) {
                window.draw(ScoreTop[i]);
            }
            window.display();
        }

    }
    return 0;
}
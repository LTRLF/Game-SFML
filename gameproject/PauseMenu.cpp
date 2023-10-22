#include "PauseMenu.h"
#define SFML_NO_DEPRECATED_WARNINGS

PauseMenu::PauseMenu(float width, float height)
{
	if (!font.loadFromFile("Next Bro.ttf"))
	{
		//handle error
	}

	pause[0].setFont(font);
	pause[0].setFillColor(sf::Color::Red);
	pause[0].setString("Resume");
	pause[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	pause[1].setFont(font);
	pause[1].setFillColor(sf::Color::White);
	pause[1].setString("Quit");
	pause[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	selectedItemIndex = 0;
}
PauseMenu::~PauseMenu()
{
}

void PauseMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(pause[i]);
	}
}

void PauseMenu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		pause[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		pause[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	else
	{
		pause[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
		pause[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void PauseMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		pause[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		pause[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	else
	{
		pause[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = 0;
		pause[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

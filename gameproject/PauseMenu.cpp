#include "PauseMenu.h"
#define SFML_NO_DEPRECATED_WARNINGS

PauseMenu::PauseMenu(float width, float height)
{
	background.setSize(sf::Vector2f	(350.0f, 300.0f));
	background.setFillColor(sf::Color(150, 150, 150, 200));
	background.setPosition(110.0f, 215.0f);

	if (!font.loadFromFile("Next Bro.ttf"))
	{
		//handle error
	}

	text.setFont(font);
	text.setString("Paused");
	text.setCharacterSize(50);
	text.setFillColor(sf::Color(255, 255, 255));
	text.setPosition(210.0f, 255.0f);

	pause[0].setFont(font);
	pause[0].setFillColor(sf::Color::Red);
	pause[0].setString("Resume");
	pause[0].setPosition(sf::Vector2f(width +26, (height+15 / (MAX_NUMBER_OF_ITEMS + 1) * 1) - 43));

	pause[1].setFont(font);
	pause[1].setFillColor(sf::Color::White);
	pause[1].setString("Back to Mainmenu");
	pause[1].setPosition(sf::Vector2f(width +26, height+50 / (MAX_NUMBER_OF_ITEMS + 2) * 2));

	selectedItemIndex = 0;
}
PauseMenu::~PauseMenu()
{
}

void PauseMenu::draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(text);

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

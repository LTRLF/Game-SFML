#include "EndGame.h"
#define SFML_NO_DEPRECATED_WARNINGS

EndGame::EndGame(float width, float height)
{
	background.setSize(sf::Vector2f(350.0f, 360.0f));
	background.setFillColor(sf::Color(150, 150, 150, 200));
	background.setPosition(110.0f, 140.0f);

	if (!font.loadFromFile("Next Bro.ttf"))
	{
		//handle error
	}

	text.setFont(font);
	text.setString("GameOver!");
	text.setCharacterSize(50);
	text.setFillColor(sf::Color(255, 255, 255));
	text.setPosition(170.0f, 200.0f);

	end[0].setFont(font);
	end[0].setFillColor(sf::Color::Red);
	end[0].setString("Play Again");
	end[0].setPosition(sf::Vector2f(width+50 / 2, (height+1 / (MAX_NUMBER_OF_ITEMS + 1) * 2) - 40));

	end[1].setFont(font);
	end[1].setFillColor(sf::Color::White);
	end[1].setString("Back to MainMenu");
	end[1].setPosition(sf::Vector2f(width+50 / 2, (height+1 / (MAX_NUMBER_OF_ITEMS + 1) * 2) + 20));

	selectedItemIndex = 0;

}

EndGame::~EndGame()
{
}

void EndGame::draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(text);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(end[i]);
	}
}

void EndGame::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		end[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		end[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	else
	{
		end[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
		end[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void EndGame::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		end[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		end[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	else
	{
		end[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = 0;
		end[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

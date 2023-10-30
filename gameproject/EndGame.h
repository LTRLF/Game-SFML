#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 2

class EndGame
{
public:
	EndGame(float width, float height);
	~EndGame();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text end[MAX_NUMBER_OF_ITEMS];
	sf::RectangleShape background;
	sf::Text text;
};
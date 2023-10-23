#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 2

class PauseMenu
{
public:
	PauseMenu(float width, float height);
	~PauseMenu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text pause[MAX_NUMBER_OF_ITEMS];
	sf::RectangleShape background;
	sf::Text text;

};
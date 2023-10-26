#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class NewMenu
{
public:
	NewMenu(float width, float height);
	~NewMenu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex;}

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};
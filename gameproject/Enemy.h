#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f &position);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	sf::RectangleShape& getBody();
	float speed;

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	bool faceRight;
};


#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f& position) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.0f, 100.0f));
	body.setPosition(position);
	body.setTexture(texture);
}

void Enemy::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);
	movement.y += deltaTime * speed;
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);

}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

sf::RectangleShape& Enemy::getBody()
{
	return body;
}

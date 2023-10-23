#pragma once
#include "SFML/Graphics.hpp"

class Logic
{
public:
	void Variables();
	void Update(float deltaTime);

private:
	unsigned points;
	int life;
};


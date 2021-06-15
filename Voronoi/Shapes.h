#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Parameters.h"

class sweepLine{
public:
	// Public features
	sf::RectangleShape sweepLineShape;

	// Constructors
	sweepLine();
	sweepLine(parameters* settings);

	// Avoid duplication
	sweepLine(const sweepLine& sweepLine) = delete;

	// Public methods
	float getY() { return y; }

	void setThickness(float thickness);
	void updatePos(sf::RenderWindow* window);

private:
	float y;
	float x1, x2;
};

class site {
public:
	// Public features
	sf::CircleShape siteShape;
	sf::VertexArray siteArc;

	// Constructors
	site();
	site(parameters* settings, int iterator);

	// Public methods
	int getX() { return this->x; }
	int getY() { return this->y; }
	void setX(int x_) { this->x = x_; }
	void setY(int y_) { this->y = y_; }

	void updateArc(parameters* settings, sweepLine* line);

private:
	int x, y;
	int siteID;
};

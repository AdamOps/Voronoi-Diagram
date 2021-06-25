#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Parameters.h"

class site {
public:
	// Public features
	sf::CircleShape siteShape;

	// Constructors
	site() : x(0), y(0) {};
	site(parameters* settings);

	// Public methods
	int getX() { return this->x; }
	int getY() { return this->y; }
	void setX(int x_) { this->x = x_; }
	void setY(int y_) { this->y = y_; }

	bool isCircle() { return false; }

private:
	int x, y;
};

class circle {
public:
	// Public features

	// Constructors
	circle() : x(0), y(0) {};
	circle(float x_, float y_) {
		x = x_;
		y = y_;
	}

	//public Methods
	int getX() { return x; }
	int getY() { return y; }
	void setX(int x_) { x = x_; }
	void setY(int y_) { y = y_; }

	bool isCircle() { return true; }

private:
	int x, y;
};
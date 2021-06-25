#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <iostream>

#include "Parameters.h"
#include "Shapes.h"

site::site(parameters* settings) {
	x = rand() % settings->windowWidth;
	y = rand() % settings->windowHeight;
	siteShape.setRadius(settings->siteRadius);
	siteShape.setPosition(sf::Vector2f(x, y));
}
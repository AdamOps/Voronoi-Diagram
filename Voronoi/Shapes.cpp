#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <iostream>

#include "Parameters.h"
#include "Shapes.h"

sweepLine::sweepLine() {
	y = 0.f;
	std::cout << "Failed to create sweepline" << std::endl;
}

sweepLine::sweepLine(parameters* settings) {
	y = 0.f;
};

void sweepLine::updatePos(sf::RenderWindow* window) { 
	y = static_cast<float>(sf::Mouse::getPosition(*window).y);
}


site::site(parameters* settings) {
	x = rand() % settings->windowWidth;
	y = rand() % settings->windowHeight;
	siteShape.setRadius(settings->siteRadius);
}
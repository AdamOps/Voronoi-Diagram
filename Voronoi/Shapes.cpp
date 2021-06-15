#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <iostream>

#include "Parameters.h"
#include "Shapes.h"

sweepLine::sweepLine() {
	y = 0;
	x1 = 0;
	x2 = 0;
	sweepLineShape.setScale(0, 0);
	std::cout << "Failed to create sweepline" << std::endl;
}

sweepLine::sweepLine(parameters* settings) {
	y = 0.f;
	x1 = 0.f;
	x2 = settings->windowWidth;
	sweepLineShape.setSize(sf::Vector2f(x2, settings->sweepLineThickness));
	sweepLineShape.setFillColor(sf::Color::White);
	sweepLineShape.setPosition(x1, y);
};

void sweepLine::updatePos(sf::RenderWindow* window) { 
	y = static_cast<float>(sf::Mouse::getPosition(*window).y);
	sweepLineShape.setPosition(x1, y);
}

void sweepLine::setThickness(float thickness) {
	sweepLineShape.setSize(sf::Vector2f(sweepLineShape.getScale().x, thickness));
}

site::site() {
	x = 0;
	y = 0;
	siteID = 0;
	std::cout << "Failed to create sites" << std::endl;
}

site::site(parameters* settings, int iterator) {
	x = rand() % settings->windowWidth;
	y = rand() % settings->windowHeight;
	siteID = iterator;

	siteShape.setRadius(settings->siteRadius);
	siteShape.setFillColor(sf::Color::Blue);
	siteShape.setOrigin(siteShape.getOrigin().x + siteShape.getRadius(), siteShape.getOrigin().y + siteShape.getRadius());
	siteShape.setPosition(static_cast<float>(x), static_cast<float>(y));

	// Define arc corresponding to the site. The linestrip has as many segments as there are pixels in the window width, to maximise the resolution.
	// Might want to reduce this a bit (for performance), since this won't actually be used for any kind of calculations, but is only there to display the arc.
	siteArc.setPrimitiveType(sf::LineStrip);
	// siteArc.resize(static_cast<int>(settings->windowWidth));
}

void site::updateArc(parameters* settings, sweepLine* line) {
	// Reset the whole arc by deleting all points inside.
	siteArc.clear();

	sf::Vertex vertex;
	for (int i = 0; i < settings->windowWidth; i++) {
		// This calculates the y value of the parabola for every x coordinate (with a resolution of 1 pixel), based on the current height of the sweep line.
		float arcY = (1 / (2 * (y - line->getY()))) * (i - x) * (i - x) + (y + line->getY()) / 2;
		vertex.position = sf::Vector2f(i, arcY);
		siteArc.append(vertex);
	}
	
}
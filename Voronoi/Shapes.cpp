#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <iostream>

#include "Parameters.h"
#include "Shapes.h"

sweepLine::sweepLine() {
	y = 0;
	sweepLineShape.setScale(0, 0);
	std::cout << "Failed to create sweepline" << std::endl;
}

sweepLine::sweepLine(parameters* settings) {
	y = 0.f;
	sweepLineShape.setSize(sf::Vector2f(settings->windowWidth, settings->sweepLineThickness));
	sweepLineShape.setFillColor(sf::Color::White);
	sweepLineShape.setPosition(0.f, y);
};

void sweepLine::updatePos(sf::RenderWindow* window) { 
	y = static_cast<float>(sf::Mouse::getPosition(*window).y);
	sweepLineShape.setPosition(0.f, y);
}

void sweepLine::setThickness(float thickness) {
	sweepLineShape.setSize(sf::Vector2f(sweepLineShape.getScale().x, thickness));
}

site::site() {
	x = 0;
	y = 0;
	siteID = 0;
	visibleToBeach = false;
	std::cout << "Failed to create sites" << std::endl;
}

site::site(parameters* settings, int iterator) {
	x = rand() % settings->windowWidth;
	y = rand() % settings->windowHeight;
	siteID = iterator;
	visibleToBeach = false;

	siteShape.setRadius(settings->siteRadius);
	siteShape.setFillColor(sf::Color::Blue);
	siteShape.setOrigin(static_cast<float>(siteShape.getOrigin().x + siteShape.getRadius()), static_cast<float>(siteShape.getOrigin().y + siteShape.getRadius()));
	siteShape.setPosition(static_cast<float>(x), static_cast<float>(y));

	// Define arc corresponding to the site. The linestrip has as many segments as there are pixels in the window width, to maximise the resolution.
	// Might want to reduce this a bit (for performance), since this won't actually be used for any kind of calculations, but is only there to display the arc.
	siteArc.setPrimitiveType(sf::LineStrip);
	siteArc.resize(static_cast<int>(settings->windowWidth / settings->arcResolution));
}

void site::updateArc(parameters* settings, sweepLine* line) {
	// Reset the whole arc by deleting all points inside.
	siteArc.clear();

	for (int i = 0; i < settings->windowWidth; i += settings->arcResolution) {
		// This calculates the y value of the parabola for every x coordinate (with a resolution of 'arcResolution' pixels), based on the current height of the sweep line.
		float arcY = (1 / (2 * (y - line->getY()))) * (i - x) * (i - x) + (y + line->getY()) / 2;
		siteArc.append(sf::Vertex(sf::Vector2f(static_cast<float>(i), arcY), sf::Color::White));
	}	
}

beachLine::beachLine() {
	beachLineArray.clear();
	sf::Vertex vertex = sf::Vector2f(50, 50);
	beachLineArray.append(vertex);
	std::cout << "Failed to create beachline" << std::endl;
}


beachLine::beachLine(std::vector<site>* siteVector, parameters* settings) {
	beachLineArray.setPrimitiveType(sf::LineStrip);
	beachLineArray.resize(static_cast<int>(settings->windowWidth / settings->arcResolution));

	updateBeachLine(siteVector, settings);
}

void beachLine::updateBeachLine(std::vector<site>* siteVector, parameters* settings) {
	beachLineArray.clear();

	float maxY = 0.f;
	for (int i = 0; i < (settings->windowWidth / settings->arcResolution); i += settings->arcResolution) {
		for (int j = 0; j < siteVector->size(); j++) {
			if (siteVector->at(j).getVisibility()) {
				if (siteVector->at(j).siteArc[i].position.y > maxY) {
					maxY = siteVector->at(j).siteArc[i].position.y;
				}
			}
		}
		beachLineArray.append(sf::Vertex(sf::Vector2f(static_cast<float>(i * settings->arcResolution), maxY), sf::Color::Red));
		maxY = 0.f;
	}
}

halfEdge::halfEdge() {

}
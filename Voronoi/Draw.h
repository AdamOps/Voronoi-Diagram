#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Shapes.h"
#include "Parameters.h"

void drawAll(sf::RenderWindow* window, parameters* settings, std::vector<site>* siteVector, sweepLine* line);
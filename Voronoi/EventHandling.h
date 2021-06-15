#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Shapes.h"

void handleEvents(sf::RenderWindow* window, parameters* settings, std::vector<site>* siteVector);
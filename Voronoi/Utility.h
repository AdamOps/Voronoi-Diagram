#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void getIntersect(sf::Vector2f vertOne, sf::Vector2f vertTwo, int lineHeight, float& x1_, float& x2_);

bool checkCollinearity(sf::Vector2f siteOne, sf::Vector2f siteTwo, sf::Vector2f siteThree);

void getCircleCenter(sf::Vector2f siteOne, sf::Vector2f siteTwo, sf::Vector2f siteThree, float& x_, float& y_);
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>

#include "EventHandling.h"
#include "Init.h"
#include "Draw.h"
#include "Parameters.h"
#include "Shapes.h"

int main(){
    parameters settings;
    std::vector<site> siteVector;
    siteVector.reserve(settings.numSites);

    sweepLine line(&settings);

    sf::RenderWindow window(sf::VideoMode(settings.windowWidth, settings.windowHeight), "Voronoi Diagrams");
    window.setFramerateLimit(settings.frameRate);

    initAll(&settings, &siteVector);

    while (window.isOpen()){
        handleEvents(&window, &settings, &siteVector);

        drawAll(&window, &settings, &siteVector, &line);
    }

    return 0;
}
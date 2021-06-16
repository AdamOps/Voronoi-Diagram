#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

#include "EventHandling.h"
#include "Init.h"
#include "Draw.h"
#include "Parameters.h"
#include "Shapes.h"

int main(){
    // Initialize unique structs and vectors, and reserve the appropriate space
    parameters settings;
    std::vector<site> siteVector;
    siteVector.reserve(settings.numSites);

    sweepLine line(&settings);
    beachLine beach(&siteVector, &settings);

    // Set up the window to draw everything into.
    sf::RenderWindow window(sf::VideoMode(settings.windowWidth, settings.windowHeight), "Voronoi Diagrams");
    window.setFramerateLimit(settings.frameRate);
    window.setKeyRepeatEnabled(settings.keyRepeat);

    // Initialize all sites and corresponding arcs
    initAll(&settings, &siteVector);

    while (window.isOpen()){
        // Handle any mouse/keyboard inputs
        handleEvents(&window, &settings, &siteVector);

        // Update and draw all sites, the corresponding arcs, the sweepline and the beachfront. Short enough not to separate out update/draw.
        drawAll(&window, &settings, &siteVector, &line, &beach);
    }

    return 0;
}
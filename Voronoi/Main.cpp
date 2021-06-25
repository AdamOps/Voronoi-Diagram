#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

#include "EventHandling.h"
#include "Init.h"
#include "Parameters.h"
#include "Shapes.h"
#include "RedBlackTree.h"
#include "Utility.h"
#include "VoronoiEvents.h"
#include "Fortune.h"

int main(){
    // Initialize unique structs and vectors, and reserve the appropriate space
    parameters settings;
    std::vector<site> siteVector;
    siteVector.reserve(settings.numSites);

    // Initialize all sites and corresponding arcs
    initAll(&settings, &siteVector);

    // Create event queue storing site events and circle events
    voronoiEventQueue eventQueue;
    for (int i = 0; i < siteVector.size(); i++) {
        voronoiEvent newEvent(&siteVector.at(i));
        eventQueue.push(newEvent);
    }

    // Set up the window to draw everything into.
    sf::RenderWindow window(sf::VideoMode(settings.windowWidth, settings.windowHeight), "Voronoi Diagrams");
    window.setFramerateLimit(settings.frameRate);
    window.setKeyRepeatEnabled(settings.keyRepeat);

    // Put the main window in focus by default
    window.requestFocus();

    while (window.isOpen()){
        // Handle any mouse/keyboard inputs
        handleEvents(&window, &settings, &siteVector);

        window.clear();

        for (int i = 0; i < siteVector.size(); i++) {
            window.draw(siteVector.at(i).siteShape);
        }

        while (eventQueue.isEmpty() == false) {
            voronoiEvent currEvent = eventQueue.pop();
            if (currEvent.isCircle()) {
                executeCircleEvent();
            }
            else {
                executeSiteEvent();
            }
        }

        window.display();
    }

    return 0;
}
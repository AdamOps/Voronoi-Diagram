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
#include "BinaryTree.h"
#include "Utility.h"
#include "VoronoiEvents.h"

int main(){
    // Initialize unique structs and vectors, and reserve the appropriate space
    parameters settings;
    std::vector<site> siteVector;
    siteVector.reserve(settings.numSites);

    // Initialize all sites and corresponding arcs
    initAll(&settings, &siteVector);

    // Create renderable beachline
    sweepLine line(&settings);

    // Create binary tree to store beachline
    binaryTreeNode* rootPtr = nullptr;
    binaryTree Tree;

    // Create event queue storing site events and circle events
    voronoiEventQueue eventQueue;
    for (int i = 0; i < siteVector.size(); i++) {
        //eventQueue.push(voronoiEvent(siteVector.at(i)));
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

        for (int i = 0; i < siteVector.size(); i++) {
            window.draw(siteVector.at(i).siteShape);
        }

    }

    return 0;
}
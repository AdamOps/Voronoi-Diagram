#include <iostream>

#include "EventHandling.h"
#include "Init.h"

void handleEvents(sf::RenderWindow* window, parameters* settings, std::vector<site>* siteVector)
{
    sf::Event event;
    while (window->pollEvent(event)){
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window->close();
            break;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab) {
            siteVector->clear();
            initAll(settings, siteVector);
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
            settings->numSites++;
            siteVector->push_back(site(settings, settings->numSites - 1));
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && settings->numSites > 2) {
            settings->numSites--;
            siteVector->pop_back();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && settings->arcResolution > 1.f) {
            settings->arcResolution--;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && settings->arcResolution < 10.f) {
            settings->arcResolution++;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
            settings->drawArcs = (1 - settings->drawArcs);
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) {
            settings->drawBeach = (1 - settings->drawBeach);
        }
    }
}
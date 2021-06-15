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

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && settings->siteRadius < 10.f) {
            for (int i = 0; i < siteVector->size(); i++) {
                siteVector->at(i).siteShape.setRadius(siteVector->at(i).siteShape.getRadius() + 1.f);
                siteVector->at(i).siteShape.setOrigin(siteVector->at(i).siteShape.getOrigin().x + 1.f, siteVector->at(i).siteShape.getOrigin().y + 1.f);
            }
            settings->siteRadius += 1.f;
            std::cout << "New radius: " << settings->siteRadius << std::endl;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && settings->siteRadius > 1.f) {
            for (int i = 0; i < siteVector->size(); i++) {
                siteVector->at(i).siteShape.setRadius(siteVector->at(i).siteShape.getRadius() - 1.f);
                siteVector->at(i).siteShape.setOrigin(siteVector->at(i).siteShape.getOrigin().x - 1.f, siteVector->at(i).siteShape.getOrigin().y - 1.f);
            }
            settings->siteRadius -= 1.f;
            std::cout << "New radius: " << settings->siteRadius << std::endl;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            std::cout << "mouseX = " << sf::Mouse::getPosition().x << ", mouseY = " << sf::Mouse::getPosition().y << std::endl;
        }
    }
}
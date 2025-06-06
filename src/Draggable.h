#ifndef DRAGGABLE_H
#define DRAGGABLE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Draggable : public sf::Sprite {
    /* Goal of this class is supposed to be able to be dragged and dropped from the mouse*/
    private:
    sf::Texture texture;
    sf::FloatRect bounds;
    bool dragging = false;

    public:

    // Constructors for the Objects
    Draggable();
    Draggable(const std::string &file_name)
        : Draggable(file_name, 32, 32) {}
    Draggable(const std::string &file_name, int width, int height)
        : Sprite(texture), dragging(false){
        if (!(texture.loadFromFile(file_name))) {
            std::cout << "Failed to load texture" << std::endl;
        }
        setTextureRect(sf::IntRect(sf::Vector2<int>(0,0),
                                              sf::Vector2<int>(width,height)));
        bounds = getLocalBounds();
        setOrigin(sf::Vector2f(bounds.size.x/2.f, bounds.size.y/2.f));
    }

    // Update the Position of the Object to always be at the Mouses Position
    void update(sf::RenderWindow& window) {
        if (dragging) {
            setPosition((sf::Vector2f)sf::Mouse::getPosition(window));
        }
    }

    // If the button is
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) {
        if (event.is<sf::Event::MouseButtonPressed>()) {
            if (getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                dragging = (dragging == true) ? false : true;
            }
        }
    }

    bool isTouchingDog(Pet& dog) {
        return dog.getGlobalBounds().findIntersection(getGlobalBounds()) != std::nullopt;
    }

    bool returnDragging() {
        return dragging;
    }
};

#endif //DRAGGABLE_H

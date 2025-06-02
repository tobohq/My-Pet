#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>
#include <iostream>
class Text : public sf::Text {
    private:
    sf::Font font;
    sf::Color color;
    std::string text;

    public:

    // Constructors
    Text() : Text("null", color) {}
    Text(const std::string& text): Text(text, color) {}

    Text(const std::string& text, sf::Color fontColor)
        :  sf::Text(font, text, 30), text(text), color(fontColor) {

        // Opening Font & Setting Font
        if (!font.openFromFile("fonts/Coolvetica Rg.otf")) {
            std::cout << "Error, did not load" << std::endl;
        }
        setFont(font);
        setFillColor(color); // Filling Color Text

        // Setting Text Origin
        sf::FloatRect textBounds = getLocalBounds(); // getting x & y cords of the object
        setOrigin(sf::Vector2f(textBounds.size.x / 2, textBounds.size.y / 2));

    }


};

#endif //TEXT_H

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "Text.h"
#include "Pet.h"

class Button : public sf::RectangleShape {
  sf::Color rect_color = sf::Color(240, 206, 221);
  sf::Color text_color = sf::Color::White;
  Text text;

  public:


  // Constructors
  Button()
    : Button(sf::Vector2f(50, 80), sf::Vector2f(0, 0), text) {
  }
  Button(Text& text)
    : Button(sf::Vector2f(50, 80), sf::Vector2f(0, 0), text){
  }

  Button(const sf::Vector2f& size, const sf::Vector2f& position, Text& text)
    : RectangleShape(size) {

    setOrigin(sf::Vector2f(size.x/2, size.y/2));
    setFillColor(rect_color);
    setPosition(position);
    sf::FloatRect rect_bounds = getGlobalBounds();

    text.setFillColor(text_color);
    text.setPosition(sf::Vector2f(rect_bounds.position.x + size.x/2, rect_bounds.position.y + size.y/2.5));

    this->text = text;
  }

  // Member Functions

  // Draw Function for Buttons so we can display the rectangle and the text
  void draw(sf::RenderWindow& window) {
    window.draw(*this);  // Draw the rectangle
    window.draw(text);   // Draw the text on top
  }

  // Hover Function
  void hover(sf::RenderWindow& window) {
    sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (getGlobalBounds().contains(mouse_pos)) {
      setFillColor(text_color);
      text.setFillColor(rect_color);
    } else {
      setFillColor(rect_color);
      text.setFillColor(text_color);
    }
  }

  // Clicked Function
  bool clicked(const sf::Event& event, sf::RenderWindow& window) {
    if (event.is<sf::Event::MouseButtonPressed>()) {
      sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

      if (getGlobalBounds().contains(mouse_pos)) {
        return true;
      }
    }
    return false;
  }

  // Set Rect color and Text Color
  void set_colors(sf::Color rect_color, sf::Color text_color){
    this->rect_color = rect_color;
    this->text_color = text_color;

    setFillColor(rect_color);
    text.setFillColor(text_color);
  }
};

#endif //BUTTON_H

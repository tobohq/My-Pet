#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "User.h"
#include "Text.h"
#include "Pet.h"
#include "Background.h"
#include <iostream>
#include <sstream>

void startGame(User &user, Pet &pet, Background &background, sf::Clock &clock, sf::RenderWindow& window);

// Fixs Precision
std::string to_string(float number);

#endif //GAME_H

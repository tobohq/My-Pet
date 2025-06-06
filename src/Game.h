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
#include "Draggable.h"

void startGame(User &user, Pet &pet, Background &background, sf::Clock &anim_clock, sf::RenderWindow& window, bool show_dog);


#endif //GAME_H

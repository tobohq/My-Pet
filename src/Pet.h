#ifndef PET_H
#define PET_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StatTimer.h"

class Pet : public sf::Sprite{
    int energy_level, hunger_level, playfullness_level, cleanliness_level;

    // in 13 seconds, decrease 1 energy
    StatTimer energy_timer, hunger_timer, playfullness_timer, cleanliness_timer;

    sf::Texture dog_sprite;
    int current_frame = 0;
    int total_frames = 18, frame_per_row = 6, frame_width = 36, frame_height = 36; // Idle


    public:
    // Constructors
    Pet()
        : Pet(sf::Vector2f(0,0)){}
    Pet(const sf::Vector2f& position)
        : Sprite(dog_sprite), energy_level(100), hunger_level(100), playfullness_level(100), cleanliness_level(100),
        energy_timer(13.f), cleanliness_timer(12.f), hunger_timer(7.5f), playfullness_timer(30.f)
    {
        // Photo (256x92) -> 18 frames,

        if (!dog_sprite.loadFromFile("pet outfits/Idle Dog.png")){
            std::cout << "Failed to Load" << std::endl;
        }
        // prevent texture bleeding
        dog_sprite.setSmooth(false);

        // Setting the image to be the first ever "sprite" in the sprite sheet
        setTextureRect(sf::IntRect(sf::Vector2<int>(0,0),
                                              sf::Vector2<int>(32,32)));

        // Getting the local bounds to set Origin
        sf::FloatRect bounds = getLocalBounds();
        setOrigin(sf::Vector2f(bounds.size.x/2.f, bounds.size.y/2.f));
        setPosition(position);

        // Resizing Sprite
        setScale(sf::Vector2f(10,10));
    }

    // Level Getters
    int getEnergy() const {
        return energy_level;
    }
    int getHunger() const {
        return hunger_level;
    }
    int getPlayfullness() const {
        return playfullness_level;
    }
    int getCleanliness() const {
        return cleanliness_level;
    }

    // Setters
    void setEnergy(int energy) {
        energy_level = energy;
    }
    void setHunger(int hunger) {
        hunger_level = hunger;
    }
    void setPlayfullness(int playfullness) {
        playfullness_level = playfullness;
    }
    void setCleanliness(int cleanliness) {
        cleanliness_level = cleanliness;
    }

    // Update Frame
    void update() {
        // Frame Size: 32x32
        if (current_frame >= total_frames) {
            current_frame = 0;
        }

        int x = (current_frame % frame_per_row) * (frame_width);
        int y = (current_frame / frame_per_row) * (frame_height);
        setTextureRect(sf::IntRect(sf::Vector2<int>(x, y), sf::Vector2<int>(frame_width, frame_height)));

        current_frame++;
    }

    // Update Mood
    void updatedMood() {
        if (energy_timer.getElapsedTime().asSeconds() > energy_timer.getInterval()) {
            // in 13 seconds, decrease 1 energy
            if (!energy_level <= 0) {
                energy_level -= 1;
            }
            energy_timer.restart();
        }

        if (cleanliness_timer.getElapsedTime().asSeconds() > cleanliness_timer.getInterval()) {
            // in 12 seconds, decrease 1 cleanliness
            if (!cleanliness_level <= 0) {
                cleanliness_level -= 1;
            }
            cleanliness_timer.restart();
        }

        if (hunger_timer.getElapsedTime().asSeconds() > hunger_timer.getInterval()) {
            // in 7.5 seconds, decrease 1 hunger
            if (!hunger_level <= 0) {
                hunger_level -= 1;
            }
            hunger_timer.restart();
        }

        if (playfullness_timer.getElapsedTime().asSeconds() > playfullness_timer.getInterval()) {
            // in 30 seconds, decrease 1 playfulness
            if (!playfullness_level <= 0) {
                playfullness_level -= 1;
            }
            playfullness_timer.restart();
        }
    }

    // Satisfy Needs

    void increaseEnergy() {
        // increases energy by 1 every 1 second
        if (energy_timer.getElapsedTime().asSeconds() > 1.f) {
            if (energy_level < 100) {
                energy_level += 1;
            }
            energy_timer.restart();
        }
        energy_timer.restart();
    }

    void increaseHunger() {
        if (hunger_level < 100) {
            if (hunger_level >= 95) {
                hunger_level += 100 - hunger_level;
            } else {
                hunger_level += 5;
            }
        }
        hunger_timer.restart();
    }

    void increaseCleanliness() {
        if (cleanliness_level < 100) {
            if (cleanliness_level >= 95) {
                cleanliness_level += 100 - cleanliness_level;
            } else {
                cleanliness_level += 5;
            }
        }
        cleanliness_timer.restart();
    }

    void increaseFun() {
        if (playfullness_level < 100) {
            if (playfullness_level >= 95) {
                playfullness_level += 100 - cleanliness_level;
            } else {
                playfullness_level += 5;
            }
        }
        playfullness_timer.restart();
    }

    // Check to see if clicked for like fun (being pet)
    bool clicked(const sf::Event& event, sf::RenderWindow& window) {
        if (event.is<sf::Event::MouseButtonPressed>()) {
            sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (getGlobalBounds().contains(mouse_pos)) {
                return true;
            }
        }
        return false;
    }
};

#endif //PET_H

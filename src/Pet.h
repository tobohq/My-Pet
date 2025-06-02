#ifndef PET_H
#define PET_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Pet : public sf::Sprite{
    float energy_level, hunger_level, playfullness_level, cleanliness_level;

    sf::Texture dog_sprite;
    int current_frame = 0;
    int total_frames = 18, frame_per_row = 6, frame_width = 36, frame_height = 36; // Idle


    public:
    // Construcotrs
    Pet()
        : Pet(sf::Vector2f(0,0)){}


    Pet(const sf::Vector2f& position)
        : Sprite(dog_sprite), energy_level(100), hunger_level(100), playfullness_level(100), cleanliness_level(100)
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
    float getEnergy() const {
        return energy_level;
    }
    float getHunger() const {
        return hunger_level;
    }
    float getPlayfullness() const {
        return playfullness_level;
    }
    float getCleanliness() const {
        return cleanliness_level;
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

    // Satisfy Needs


    // Check to see if clicked for like fun (being pet)

    //
};

#endif //PET_H

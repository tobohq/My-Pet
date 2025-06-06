#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <iostream>
#include <set>

#include <SFML/Graphics.hpp>
#include <iostream>

class Background : public sf::Sprite{
    private:
    sf::Texture background;
    bool loaded = false;
    int current_frame = 0;
    int total_frame = 8, frame_per_row = 4, frame_width = 260, frame_height = 132;

    public:
    Background();
    Background(const std::string& image)
        : Background(image, sf::Vector2f(0, 0)) {}

    Background(const std::string& image, const sf::Vector2f &position)
        : Sprite(background){
        if (!background.loadFromFile(image)) {
            std::cout << "Failed to load background image" << std::endl;
        }
        setTextureRect(sf::IntRect(sf::Vector2<int>(0,0),sf::Vector2<int>(256,128)));

        // Getting the local bounds to set Origin
        sf::FloatRect bounds = getLocalBounds();
        setOrigin(sf::Vector2f(bounds.size.x/2.f, bounds.size.y/2.f));
        setPosition(position);
        setScale(sf::Vector2f(6.05f, 6.15f));
    }

    // Setters
    void setBackground(const std::string& image, const sf::Vector2f &position, int photo_width, int photo_height) {
        if (!background.loadFromFile(image)) {
            std::cout << "Failed to load background image" << std::endl;
        }
        setTextureRect(sf::IntRect(sf::Vector2<int>(0,0),sf::Vector2<int>(photo_width,photo_height)));

        // Getting the local bounds to set Origin
        sf::FloatRect bounds = getLocalBounds();
        setOrigin(sf::Vector2f(bounds.size.x/2.f, bounds.size.y/2.f));
        setPosition(position);
        setScale(sf::Vector2f(6.05f, 6.15f));
    }

    void setTotalFrame(int frame) {
        total_frame = frame;
    }
    void setFramePerRow(int frame) {
        frame_per_row = frame;
    }
    void setFrameWidth(int frame) {
        frame_width = frame;
    }
    void setFrameHeight(int frame) {
        frame_height = frame;
    }

    void setFrameDimensions(int total_frame, int frame_per_row, int frame_width, int frame_height) {
        setTotalFrame(total_frame);
        setFramePerRow(frame_per_row);
        setFrameWidth(frame_width);
        setFrameHeight(frame_height);
    }

    void update() {
        // if the frame is above the total frame, go back to the beginning photo of sprite
        if (current_frame >= total_frame) {
            current_frame = 0;
        }

        // getting the current frames dimensions by multiplying it by its width/height based on the number of frame
        // we're currently on.
        int x = (current_frame % frame_per_row) * (frame_width);
        int y = (current_frame / frame_per_row) * (frame_height);

        // setting the snippet of the frame, by getting the position/size of the frame.
        setTextureRect(sf::IntRect(sf::Vector2<int>(x, y), sf::Vector2<int>(frame_width, frame_height)));

        // go to the next frame
        current_frame++;
    }
};

#endif //BACKGROUND_H

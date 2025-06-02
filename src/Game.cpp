#include "Game.h"

void startGame(User &user, Pet &pet, Background &background, sf::Clock &clock, sf::RenderWindow& window) {
    // Getting our window dimensions.
    sf::Vector2u window_size = window.getSize();

    // Seconds Per Frame
    float frame_delay = 0.15f;

    // Displaying Background & Pet

    // If the clock goes over our seconds per frame, update to the next frame
    if (clock.getElapsedTime().asSeconds() >= frame_delay) {
        background.update(); // switching backgrounds frame
        pet.update(); // switching pets frame
        clock.restart(); // restarts timer
    }
    window.draw(background);
    window.draw(pet); // Draw pet on top of background

    // Creating a Text object to display our coins
    Text coins_text("Coins: " + std::to_string(user.getCoins()), sf::Color(247,178,66,255));

    // Setting the text position & then displaying
    sf::Vector2f position = sf::Vector2f(window_size.x - window_size.x/15.f, window_size.y/17.0f );
    coins_text.setPosition(position);
    window.draw(coins_text);

    // Pet's Status Text:
    std::vector<Text*> stats_texts = {
         new Text("Energy: " + to_string(pet.getEnergy()), sf::Color(247,178,66,255)),
         new Text("Hunger: " + to_string(pet.getHunger()), sf::Color(247,178,66,255)),
         new Text("Playfulness: " + to_string(pet.getPlayfullness()), sf::Color(247,178,66,255)),
         new Text("Cleanliness: " + to_string(pet.getCleanliness()), sf::Color(247,178,66,255))
    };

    float window_y = window_size.y/17.f;
    for (auto text_object : stats_texts) {
        // Setting Origin so it's left aligned
        sf::FloatRect bounds = text_object->getLocalBounds();
        text_object->setOrigin(sf::Vector2f(0, bounds.size.y/2));

        // Setting position to be on the left upper corner of screen
        position = sf::Vector2f(window_size.x/28.f, window_y);
        text_object->setPosition(position);

        // The next text object will be 50 px below the prev, display
        window_y += 50;
        window.draw(*text_object);
        delete text_object; // avoiding memory leak
    }

    // Pet Decreasing Mood

    window.draw(pet);
}

std::string to_string(float number) {
    std::ostringstream stream; // creating string stream
    stream.precision(1); // how much decimals to show in the stream
    stream << std::fixed << number; // forces the number to insert in the stream in the fixed-point format
    return stream.str(); // converts content of the stream to a string
}


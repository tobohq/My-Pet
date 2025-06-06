#include "Game.h"

void startGame(User &user, Pet &pet, Background &background, sf::Clock &anim_clock, sf::RenderWindow& window, bool show_dog) {
    // Getting our window dimensions.
    sf::Vector2u window_size = window.getSize();

    // Seconds Per Frame
    float frame_delay = 0.15f;

    // If the clock goes over our seconds per frame, update to the next frame
    if (anim_clock.getElapsedTime().asSeconds() >= frame_delay) {
        background.update(); // switching backgrounds frame
        pet.update(); // switching pets frame
        anim_clock.restart(); // restarts timer
    }
    window.draw(background);

    // Creating a Text object to display our coins
    Text coins_text("Coins: " + std::to_string(user.getCoins()), sf::Color(247,178,66,255));

    // Setting the text position & then displaying
    sf::Vector2f position = sf::Vector2f(window_size.x - window_size.x/15.f, window_size.y/17.0f );
    coins_text.setPosition(position);
    window.draw(coins_text);

    // Pet's Status Text:
    std::vector<Text*> stats_texts = {
         new Text("Energy: " + std::to_string(pet.getEnergy()), sf::Color(247,178,66,255)),
         new Text("Hunger: " + std::to_string(pet.getHunger()), sf::Color(247,178,66,255)),
         new Text("Playfulness: " + std::to_string(pet.getPlayfullness()), sf::Color(247,178,66,255)),
         new Text("Cleanliness: " + std::to_string(pet.getCleanliness()), sf::Color(247,178,66,255))
    };

    float window_y = window_size.y/17.f;
    sf::RectangleShape background_text(sf::Vector2f(250, window_y + (40 * stats_texts.size())));
    background_text.setOrigin(sf::Vector2f(background_text.getSize().x / 2, background_text.getSize().y / 2));
    background_text.setPosition(sf::Vector2f(window_size.x/9.5f, window_y+80));
    background_text.setFillColor(sf::Color(0,94,36,255));

    window.draw(background_text);

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

    if (show_dog) {
        pet.updatedMood();
        window.draw(pet);
    }

    user.saveToFile();
}

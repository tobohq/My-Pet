#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Text.h"
#include "Game.h"
#include "User.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(160);
    sf::Vector2u window_size = window.getSize();
    std::cout << "Window: ( " << window_size.x << " , " << window_size.y << std::endl;
    bool show_buttons = true;

    // Window Poisitioning
    float x_center = window_size.x / 2.0;
    float y_center = window_size.y / 2.0;

    // Objects
    Text new_user("New User"); // Text
    Text continuing("Continue"); // Text
    Text buy_food_txt("Buy Food (-5)");
    Text sleep_txt("Sleep");
    buy_food_txt.setCharacterSize(27);
    sleep_txt.setCharacterSize(27);

    Background outside("backgrounds/Outside Background.png",
                sf::Vector2f(window_size.x/2.f, window_size.y/2.06f)); // Background of Pet Screen

    // Clocks
    sf::Clock animation_clock; // Clock for animation
    sf::Clock soapContactClock;
    sf::Clock foodContactClock;
    sf::Clock coinClock;

    // Draggable Objects
    std::vector<Draggable*> foods_list;

    Draggable soap("Objects/Soap.png", 32, 32);
    soap.setPosition(sf::Vector2f(window.getSize().x - window.getSize().x/11, window.getSize().y/1.4f));
    soap.setScale(sf::Vector2f(5,5));

    // Buttons
    Button new_user_button(sf::Vector2f(150,90), sf::Vector2f(x_center-x_center/4, y_center), new_user);
    Button continue_button(sf::Vector2f(150,90), sf::Vector2f(x_center+x_center/4, y_center), continuing);
    Button buy_food(sf::Vector2f(190,50),
        sf::Vector2f(window_size.x - window_size.x/14.f, window_size.y/7.2f),
        buy_food_txt);
    Button sleep_button(sf::Vector2f(190,50),
        sf::Vector2f(window_size.x - window_size.x/14.f, window_size.y/4.3f),
        sleep_txt);

    buy_food.set_colors(sf::Color(0,94,36,255), sf::Color(247,178,66,255));
    buy_food.setOutlineColor(sf::Color(76, 40, 25));
    buy_food.setOutlineThickness(4.f);

    sleep_button.set_colors(sf::Color(0,94,36,255), sf::Color(247,178,66,255));
    sleep_button.setOutlineColor(sf::Color(76, 40, 25));
    sleep_button.setOutlineThickness(4.f);

    User *user = nullptr; // Point to a User Object

    // Boolean Statements
    bool show_dog = true;
    bool soapTouchingDog = false;
    bool foodTouchingDog = false;

    // int index
    int index = 0;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // FOR THE MAIN MENU
            if (show_buttons) {

                // Button Hover
                continue_button.hover(window);
                new_user_button.hover(window);

                // Buttons Clicked

                // Continue Button Clicked
                if (continue_button.clicked(*event,  window)) {
                    // If continued game, read the file and updated the contents/
                    std::cout << "<Continued Game Ran>" << std::endl;
                    show_buttons = false;


                    std::ifstream user_file("User Data"); //
                    user = new User(user_file); // Points to a
                    user->getPet().setPosition(sf::Vector2f(x_center, window_size.y-window_size.y/3.0));
                    for (int i=0; i < foods_list.size(); i++) {
                        auto* new_food = new Draggable("Objects/chicken.png", 32, 32);
                        new_food->setPosition(sf::Vector2f(window.getSize().x / 7+i, window.getSize().y / 1.4f));
                        new_food->setScale(sf::Vector2f(6, 6));
                        foods_list.push_back(new_food);
                        window.draw(*new_food);
                    }
                }

                // New User Button Clicked
                if (new_user_button.clicked(*event,  window)) {
                    std::cout << "<New Game Ran>" << std::endl;
                    show_buttons = false;

                    std::ofstream user_file("User Data");
                    user = new User(user_file);
                    user->getPet().setPosition(sf::Vector2f(x_center, window_size.y-window_size.y/3.0));

                    auto* new_food = new Draggable("Objects/chicken.png", 32, 32);
                    new_food->setPosition(sf::Vector2f(window.getSize().x / 7, window.getSize().y / 1.4f));
                    new_food->setScale(sf::Vector2f(6, 6));
                    foods_list.push_back(new_food);
                }
            } else { // NOT THE MAIN MENU, WHERE OUR GAME BEGINS
                // looks if the mouse is interacting with the dog
                if (show_dog) {
                    if (user->getPet().clicked(*event,  window)) {
                        user->getPet().increaseFun();
                    }

                    for (auto it = foods_list.begin(); it != foods_list.end();) {
                        Draggable* item = *it;
                        item->handleEvent(*event, window);
                        item->update(window);

                        if (item->isTouchingDog(user->getPet())) {
                            if (!foodTouchingDog) {
                                foodTouchingDog = true;
                                foodContactClock.restart();
                            }

                            if (foodContactClock.getElapsedTime().asSeconds() >= 1.f) {
                                user->getPet().increaseHunger();
                                user->increaseCoins();
                                delete item;
                                it = foods_list.erase(it);
                                foodTouchingDog = false;
                                continue;
                            }
                        }
                        ++it; // Only increment if we didn’t erase
                    }


                    // Checking to see if the soap is interacting with the dog
                    soap.handleEvent(*event, window);
                    soap.update(window);
                    if (soap.isTouchingDog(user->getPet())) {
                        if (!soapTouchingDog) {
                            soapTouchingDog = true;
                            soapContactClock.restart(); // Start timing the contact
                        }

                        if (soapContactClock.getElapsedTime().asSeconds() >= 1.f) {
                            user->getPet().increaseCleanliness();
                            if (!(user->getPet().getCleanliness() > 100)) {
                                user->increaseCoins();
                            }
                            soapTouchingDog = false;
                        }
                    } else {
                        // Reset everything if not touching
                        soapTouchingDog = false;
                    }
                }

                // looks through to see if our food list is interacting with the do

                // Button Hover
                buy_food.hover(window);
                sleep_button.hover(window);

                // Buying Food
                if (buy_food.clicked(*event, window)) {
                    if (user->getCoins() >= 5) {
                        user->setFoodStorage(user->getFoodStorage() + 1);
                        user->setCoins(user->getCoins() - 5);

                        auto new_food = new Draggable("Objects/chicken.png", 32, 32);
                        new_food->setPosition(sf::Vector2f(window.getSize().x / 7, window.getSize().y / 1.4f));
                        new_food->setScale(sf::Vector2f(6, 6));
                        foods_list.push_back(new_food);
                    }
                }

                // Sleeping Button
                if (sleep_button.clicked(*event, window)) {
                    if (!show_dog) { // if show dog is false and this button is clicked again then make dog appear
                        outside.setFrameDimensions(8, 4, 260, 132);
                        outside.setBackground("backgrounds/Outside Background.png",
                            sf::Vector2f(window_size.x/2.f, window_size.y/2.06f),
                            256, 128);
                        show_dog = true;
                    } else { // if show dog is true, and sleep button clicked then mimis time
                        outside.setBackground("backgrounds/Night Time.PNG",
                            sf::Vector2f(window_size.x/2.f, window_size.y/2.06f),
                            256, 128);
                        outside.setFrameDimensions(16, 8, 260, 132);
                        show_dog = false;
                    }
                }

                // Updating the coins for when they're asleep
                if (!show_dog) {
                    if (coinClock.getElapsedTime().asSeconds() >= 1.f) {
                        user->increaseCoins();
                        user->getPet().increaseEnergy();  // <-- add this line
                        coinClock.restart();
                    }
                }
            }

        }
        window.clear(sf::Color(255, 250, 252));

        if (show_buttons) {
            new_user_button.draw(window);
            continue_button.draw(window);
        } else {
            startGame(*user, user->getPet(), outside, animation_clock, window, show_dog);

            // Drawning the Buttons
            buy_food.draw(window);
            sleep_button.draw(window);

            // Drawing the Objects like Food & Soap
            window.draw(soap);
            // All Foood
            for (auto* food : foods_list) {
                window.draw(*food);
            }
        }
        window.display();
    }
    delete user;
}

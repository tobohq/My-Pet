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

    // Draggable Objects
    std::vector<Draggable*> foods_list;
    foods_list.clear();

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

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>()) {
                window.close();
                for (auto it = foods_list.begin(); it != foods_list.end();) {
                    delete *it;
                    it = foods_list.erase(it);
                }
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

                    // If there was previous food stored/bought add them back
                    for (int i=0; i < user->getFoodStorage(); i++) {
                        auto* new_food = new Draggable("Objects/chicken.png", 32, 32);
                        new_food->setPosition(sf::Vector2f(window.getSize().x/7, window.getSize().y / 1.4f));
                        new_food->setScale(sf::Vector2f(6, 6));
                        foods_list.push_back(new_food); // add it to our vector
                    }
                }

                // New User Button Clicked
                if (new_user_button.clicked(*event,  window)) {
                    std::cout << "<New Game Ran>" << std::endl;
                    show_buttons = false;

                    std::ofstream user_file("User Data");
                    user = new User(user_file);
                    user->getPet().setPosition(sf::Vector2f(x_center, window_size.y-window_size.y/3.0));

                    // New Users will always start with 1 food item
                    auto* new_food = new Draggable("Objects/chicken.png", 32, 32);
                    new_food->setPosition(sf::Vector2f(window.getSize().x/7, window.getSize().y / 1.4f));
                    new_food->setScale(sf::Vector2f(6, 6)); // match your later logic
                    foods_list.push_back(new_food);
                }
            } else { // NOT THE MAIN MENU, WHERE OUR GAME BEGINS
                // looks if the mouse is interacting with the dog
                if (show_dog) {
                    if (user->getPet().clicked(*event,  window)) {
                        user->getPet().increaseFun();
                    }

                    for (auto it = foods_list.begin(); it != foods_list.end();) {
                        (*it)->handleEvent(*event, window);
                        (*it)->update(window);

                        // IF THE DOG ISN'T HUNGRY IT SHOULDN'T BE ABLE TO EAT
                        if (user->getPet().getHunger() < 100){
                            if ((*it)->isTouchingDog(user->getPet())) {
                                if (!foodTouchingDog) { // if the food was previously not touching dog
                                    foodTouchingDog = true; // make it touch
                                    foodContactClock.restart(); // wait a few seconds before making the dog eat it
                                }

                                if (foodContactClock.getElapsedTime().asSeconds() >= 1.f) {
                                    user->getPet().increaseHunger(5); // increases hunger by 5
                                    user->increaseCoins(); // Increases coins when fed

                                    delete (*it); // delete the food item
                                    it = foods_list.erase(it); // erase from the vector, and go to the next one
                                    user->decreaseFoodStorage(1); // decrease food storage by 1 when it gets eaten by dog

                                    foodTouchingDog = false; // no more food touching
                                    continue; // dont iterate since we already did with erase
                                }
                            }
                        }
                        ++it; // only increment's the positition if we didn’t erase
                    }


                    // Checking to see if the soap is interacting with the dog
                    soap.handleEvent(*event, window);
                    soap.update(window);
                    // Similar to the dog logic except dont delete the soap.
                    if (user->getPet().getCleanliness() < 100) {
                        if (soap.isTouchingDog(user->getPet())) {
                            if (!soapTouchingDog) {
                                soapTouchingDog = true;
                                soapContactClock.restart(); // Start timing the contact
                            }

                            if (soapContactClock.getElapsedTime().asSeconds() >= 1.f) {
                                user->getPet().increaseCleanliness();
                                user->increaseCoins();
                                soapTouchingDog = false;
                            }
                        }
                    }
                }

                // Button Hover
                buy_food.hover(window);
                sleep_button.hover(window);

                // Buying Food
                if (buy_food.clicked(*event, window)) {
                    if (user->getCoins() >= 5) {
                        user->setFoodStorage(user->getFoodStorage() + 1);
                        user->setCoins(user->getCoins() - 5);

                        // Create a new food object
                        auto new_food = new Draggable("Objects/chicken.png", 32, 32);
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
            // Draw all Foood
            int width = window.getSize().x/7; // the width of the location of ham
            for (auto it = foods_list.begin(); it != foods_list.end();) {
                if (!(*it)->returnDragging()) {
                    (*it)->setPosition(sf::Vector2f(width, window.getSize().y / 1.4f));
                    width += (*it)->getWidth()/1.3;
                }
                (*it)->setScale(sf::Vector2f(6, 6));
                window.draw(**it);
                ++it;
            }
        }
        window.display();
    }
    delete user;
}

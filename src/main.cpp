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
    Text new_user("New User");
    Text continuing("Continue");
    Pet user_pet(sf::Vector2f(x_center, window_size.y-window_size.y/3.0));
    Background outside("backgrounds/Outside Background.png",
                sf::Vector2f(window_size.x/2.f, window_size.y/2.06f));
    sf::Clock animation_clock;

    Button new_user_button(sf::Vector2f(150,90), sf::Vector2f(x_center-x_center/4, y_center), new_user);
    Button continue_button(sf::Vector2f(150,90), sf::Vector2f(x_center+x_center/4, y_center), continuing);

    User user;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (show_buttons) {

                // Button Hover
                continue_button.hover(window);
                new_user_button.hover(window);

                // Buttons Clicked
                if (continue_button.clicked(*event,  window)) {
                    std::cout << "<Continued Game Ran>" << std::endl;
                    show_buttons = false;

                    std::ifstream user_file("User Data");
                    User existing_user(user_file);
                    user = existing_user;
                }

                if (new_user_button.clicked(*event,  window)) {
                    std::cout << "<New Game Ran>" << std::endl;
                    show_buttons = false;

                    std::ofstream user_file("User Data");
                    User new_user(user_file);
                    user = new_user;
                }
            }

        }
        window.clear(sf::Color(255, 250, 252));

        if (show_buttons) {
            new_user_button.draw(window);
            continue_button.draw(window);
        } else {
            startGame(user, user_pet, outside, animation_clock, window);
        }
        window.display();
    }
}

#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    std::cout << "Program started\n";

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Ball Clicker Game");

    std::cout << "Window created\n";

    while(window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
#pragma once

#include <SFML/Graphics.hpp>

class Ball {
    public:
        Ball(float x, float y, float dx, float dy, float radius);
        void draw(sf::RenderWindow &window);
        void update(float deltaTime, sf::Vector2u windowSize);
        bool clicked(sf::Vector2i clickedPosition);
        void erase();
        bool isAlive();

    private:
        sf::CircleShape shape;
        sf::Vector2f velocity;
        bool alive;
};
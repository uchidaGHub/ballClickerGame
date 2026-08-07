#include "Ball.h"

Ball::Ball(float x, float y, float dx, float dy, float radius) {
    shape.setRadius(radius);
    shape.setOrigin({radius, radius});
    shape.setPosition({x, y});
    shape.setFillColor(sf::Color::Blue);
    velocity = {dx, dy};
    alive = true;
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Ball::update(float deltaTime, sf::Vector2u windowSize) {
    sf::Vector2f position = shape.getPosition();
    float radius = shape.getRadius();

    if (position.x <= radius || position.x >= windowSize.x - radius) {
        velocity.x *= -1;
    }

    if (position.y <= radius || position.y >= windowSize.y - radius) {
        velocity.y *= -1;
    }

    position += deltaTime * velocity;
    shape.setPosition(position);
}

bool Ball::clicked(sf::Vector2i clickedPosition) {
    sf::Vector2f shapePosition = shape.getPosition();
    sf::Vector2f difference = sf::Vector2f(clickedPosition) - shapePosition;
    float radius = shape.getRadius();

    return difference.lengthSquared() <= radius * radius;
}

void Ball::erase() {
    alive = false;
}

bool Ball::isAlive() {
    return alive;
}
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <iostream>
#include <random>

void spawnBalls(std::vector<Ball> &listBalls, int numBalls, sf::Vector2u &windowSize, std::mt19937 &generator);
void handleClick(std::vector<Ball> &listBalls, sf::Vector2i &clickedPosition);
void drawWin(sf::Font &font, sf::RenderWindow &window);

int main() {
    sf::Vector2u windowSize = {800, 600};
    sf::RenderWindow window(sf::VideoMode(windowSize), "Ball Clicker Game");
    sf::Clock clock;
    sf::Font font;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::cout << std::filesystem::current_path() << '\n';

    if (!font.openFromFile("C:\\Users\\ucma1\\Documents\\personalProgramming\\ballClickerGame\\assets\\arial.ttf")) {
        std::cerr << "Failed to load font\n";
        return 1;
    }

    int numBalls = 5;
    std::vector<Ball> listBalls;
    spawnBalls(listBalls, numBalls, windowSize, generator);

    while(window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        bool gameWin = false;

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto *mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2i clickedPosition = mousePressed->position;
                    handleClick(listBalls, clickedPosition);
                }
            }
        }

        for (std::size_t i = 0; i < listBalls.size(); ++i) {
            if (!listBalls[i].isAlive()) {
                listBalls.erase(listBalls.begin() + i);
            }
        }

        if (listBalls.empty()) {
            gameWin = true;
        }
        
        for (Ball &ball : listBalls) {
            ball.update(deltaTime, windowSize);
        }
        
        window.clear();

        for (Ball &ball : listBalls) {
            ball.draw(window);
        }

        if (gameWin) {
            drawWin(font, window);
        }

        window.display();
    }
}

void spawnBalls(std::vector<Ball> &listBalls, int numBalls, sf::Vector2u &windowSize, std::mt19937 &generator) {
    float radius = 10.f;

    std::uniform_real_distribution<float> xDist(radius, windowSize.x - radius);
    std::uniform_real_distribution<float> yDist(radius, windowSize.y - radius);
    std::uniform_real_distribution<float> speedDist(0.0, 200.0);

    for (int i = 0; i < numBalls; i++) {
        float x = xDist(generator);
        float y = yDist(generator);
        float dx = speedDist(generator);
        float dy = 200.0 - dx;

        listBalls.emplace_back(x, y, dx, dy, radius);
    }
};

void handleClick(std::vector<Ball> &listBalls, sf::Vector2i &clickedPosition) {
    for (Ball &ball : listBalls) {
        if (ball.clicked(clickedPosition)) {
            ball.erase();
        }
    }
}

void drawWin(sf::Font &font, sf::RenderWindow &window) {
    sf::Text text(font);
    sf::Vector2u windowSize = window.getSize();
    sf::FloatRect textBounds;

    text.setString("YOU WIN!");
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::Yellow);

    textBounds = text.getLocalBounds();
    text.setOrigin({textBounds.position.x + textBounds.size.x / 2.f, textBounds.position.y + textBounds.size.y / 2.f});
    text.setPosition({windowSize.x / 2.f, windowSize.y / 2.f});

    window.draw(text);
}
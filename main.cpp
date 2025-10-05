#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <algorithm>

bool isColliding(const sf::RectangleShape& rect, const sf::CircleShape& circle);

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Pong");
    sf::Clock startClock;
    const float startDelay = 1.f;
    bool gameStarted = false;
    int leftPaddleScore = 0;
    int rightPaddleScore = 0;


    sf::Font font;
    if (!font.openFromFile("./fonts/Minecraft.ttf")) {
      std::cout << "Font did not load" << std::endl;
    }
    sf::Text leftText(font, std::to_string(leftPaddleScore), 48);
    leftText.setPosition({176.f, 100.f});
    sf::Text rightText(font, std::to_string(rightPaddleScore), 48);
    rightText.setPosition({576.f, 100.f});

    sf::RectangleShape leftPaddle({20, 100});
    leftPaddle.setPosition({0.f, 250.f});
    leftPaddle.setFillColor(sf::Color::White);

    sf::RectangleShape rightPaddle({20, 100});
    rightPaddle.setPosition({780.f, 250.f});
    rightPaddle.setFillColor(sf::Color::White);

    sf::CircleShape ball(5.f);
    ball.setPosition({400.f, 300.f});
    ball.setFillColor(sf::Color::Blue);
    sf::Vector2f ballVelocity{4.f, 4.f};
    ball.setOrigin({ball.getRadius(), ball.getRadius()});

    std::vector<sf::RectangleShape> centerline;
    for (int i = 0; i < 600; i += 30) {
      sf::RectangleShape dash({5.f, 20.f});
      dash.setPosition({397.5f, (float)i});
      dash.setFillColor(sf::Color::White);
      centerline.push_back(dash);
    }

    while (window.isOpen()) {
        while (auto eventOpt = window.pollEvent()) {
            sf::Event event = *eventOpt;
            if (event.is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            leftPaddle.move({0.f, -6.f});
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            leftPaddle.move({0.f, 6.f});
        }
        if (leftPaddle.getPosition().y < 0) {
            leftPaddle.setPosition({leftPaddle.getPosition().x, 0});
        } else if (leftPaddle.getPosition().y + leftPaddle.getSize().y > 600) {
            leftPaddle.setPosition({leftPaddle.getPosition().x, 600 - leftPaddle.getSize().y});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            rightPaddle.move({0.f, -6.f});
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            rightPaddle.move({0.f, 6.f});
        }
        if (rightPaddle.getPosition().y < 0) {
            rightPaddle.setPosition({rightPaddle.getPosition().x, 0});
        } else if (rightPaddle.getPosition().y + rightPaddle.getSize().y > 600) {
            rightPaddle.setPosition({rightPaddle.getPosition().x, 600 - rightPaddle.getSize().y});
        }

        float elapsed = startClock.getElapsedTime().asSeconds();
        if (elapsed >= startDelay) {
            gameStarted = true;
        }

        if (gameStarted) {
            ball.move(ballVelocity);
            if (ball.getPosition().y - ball.getRadius() <= 0 || ball.getPosition().y + ball.getRadius() >= 600) {
                ballVelocity.y = -ballVelocity.y;
            }
            if (isColliding(leftPaddle, ball)) {
                ballVelocity.x = std::abs(ballVelocity.x);
                leftPaddleScore += 1;
                leftText.setString(std::to_string(leftPaddleScore));
            }
            if (isColliding(rightPaddle, ball)) {
                ballVelocity.x = -std::abs(ballVelocity.x);
                rightPaddleScore += 1;
                rightText.setString(std::to_string(rightPaddleScore));
            }
            if (ball.getPosition().x < 0 || ball.getPosition().x > 800) {
                ball.setPosition({400.f, 300.f});
                leftPaddleScore = 0;
                rightPaddleScore = 0;
                leftText.setString(std::to_string(0));
                rightText.setString(std::to_string(0));
                startClock.restart();
                gameStarted = false;
            }
        }

        window.clear(sf::Color::Black);
        for (auto& dash : centerline) window.draw(dash);
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.draw(leftText);
        window.draw(rightText);
        window.display();
    }
}

bool isColliding(const sf::RectangleShape& rect, const sf::CircleShape& circle) {
    auto rectBounds = rect.getGlobalBounds();
    auto circleCenter = circle.getPosition();
    float radius = circle.getRadius();
    float closestX = std::clamp(circleCenter.x, rectBounds.position.x, rectBounds.position.x + rectBounds.size.x);
    float closestY = std::clamp(circleCenter.y, rectBounds.position.y, rectBounds.position.y + rectBounds.size.y);
    float dx = circleCenter.x - closestX;
    float dy = circleCenter.y - closestY;
    return (dx*dx + dy*dy) < (radius * radius);
}

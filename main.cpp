#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <algorithm>

bool isColliding(const sf::RectangleShape& rect, const sf::CircleShape& circle);

int main() {
  //game window
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Pong");

  //game objects
  //leftPaddle
  sf::RectangleShape leftPaddle({20, 100});
  leftPaddle.setPosition({0.f, 250.f});
  leftPaddle.setFillColor(sf::Color::White); 

  //rightPaddle
  sf::RectangleShape rightPaddle({20, 100});
  rightPaddle.setPosition({780.f, 250.f});
  rightPaddle.setFillColor(sf::Color::White);

  //ball
  sf::CircleShape ball(5.f);
  ball.setPosition({390.f, 295.f});
  ball.setFillColor(sf::Color::White);
  sf::Vector2f ballVelocity{4.f, 4.f};
  ball.setOrigin({ball.getRadius(), ball.getRadius()});

  while (window.isOpen()) { //gameloop
    while (auto eventOpt = window.pollEvent()) {
      sf::Event event = *eventOpt;

      if (event.is<sf::Event::Closed>()) {
        window.close();
      }
    }
   
  //inputs
  //left paddle inputs and bounds
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    leftPaddle.move({0.f, -5.f});
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    leftPaddle.move({0.f, 5.f});
  }
  if (leftPaddle.getPosition().y < 0) {
    leftPaddle.setPosition({leftPaddle.getPosition().x, 0});
  } else if (leftPaddle.getPosition().y + leftPaddle.getSize().y > 600) {
    leftPaddle.setPosition({leftPaddle.getPosition().x, 600 - leftPaddle.getSize().y});
  }

  //right paddle inputs and bounds
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
    rightPaddle.move({0.f, -5.f});
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
    rightPaddle.move({0.f, 5.f});
  }
  if (rightPaddle.getPosition().y < 0) {
    rightPaddle.setPosition({rightPaddle.getPosition().x, 0});
  } else if (rightPaddle.getPosition().y + rightPaddle.getSize().y > 600) {
    rightPaddle.setPosition({rightPaddle.getPosition().x, 600 - rightPaddle.getSize().y});
  }
  
  //ball collisions
  ball.move(ballVelocity);
  if (ball.getPosition().y - ball.getRadius() <=0 || ball.getPosition().y + ball.getRadius() >=600) {
    ballVelocity.y = -ballVelocity.y;
  }

  //bar and ball collisons
  if (isColliding(leftPaddle, ball)) {
    ballVelocity.x = std::abs(ballVelocity.x);
  } 
  if (isColliding(rightPaddle, ball)) {
    ballVelocity.x = -std::abs(ballVelocity.x);
  }

  //reset ball
  if (ball.getPosition().x < 0 || ball.getPosition().x > 800) {
    ball.setPosition({390.f, 295.f});
  }

  //drawing stuff to the window
  window.clear(sf::Color::Black);
  window.draw(leftPaddle);
  window.draw(rightPaddle);
  window.draw(ball);
  window.display();

  }
}


bool isColliding(const sf::RectangleShape& rect, const sf::CircleShape& circle) {
    auto rectBounds = rect.getGlobalBounds();   // sf::Rect<float>
    auto circleCenter = circle.getPosition();
    float radius = circle.getRadius();

    // SFML 3: use position.x/y and size.x/y instead of left/top/width/height
    float closestX = std::clamp(circleCenter.x, rectBounds.position.x, rectBounds.position.x + rectBounds.size.x);
    float closestY = std::clamp(circleCenter.y, rectBounds.position.y, rectBounds.position.y + rectBounds.size.y);

    float dx = circleCenter.x - closestX;
    float dy = circleCenter.y - closestY;

    return (dx*dx + dy*dy) < (radius * radius);
}


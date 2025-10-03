#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

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

  //drawing stuff to the window
  window.clear(sf::Color::Black);
  window.draw(leftPaddle);
  window.draw(rightPaddle);
  window.draw(ball);
  window.display();

  }
}

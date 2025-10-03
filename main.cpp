#include <SFML/Graphics.hpp>
#include <optional>

int main() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "sfml window test");

  while (window.isOpen()) {
    while (auto eventOpt = window.pollEvent()) {
      sf::Event event = *eventOpt;

      if (event.is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear(sf::Color::Black);
    window.display();
  }

  return 0;
}

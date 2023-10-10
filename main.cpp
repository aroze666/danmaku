#include "Game.hpp"
#include <SFML/Graphics.hpp>
int main(int argc, char *argv[]) {
  sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML works!");
  window.setFramerateLimit(60);
  // window.setMouseCursorVisible(false);
  Game game(window);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    game.GeneralEvent();
    game.CollisionEvent();
    game.Update();
    window.clear(sf::Color(128, 128, 128, 255));
    window.draw(game);
    window.display();
  }
  return 0;
}

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Crosshair.hpp"
int main(int argc, char *argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	Game game(window);
	while (window.isOpen())
	{
		Crosshair crosshair(10, sf::Color::Red, window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		game.GeneralEvent();
		game.CollisionEvent();
		game.Update();
		window.clear();
		window.draw(crosshair);
		window.draw(game);
		window.display();
	}
	return 0;
}

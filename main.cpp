#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "Game.hpp"
#include "Crosshair.hpp"
int main(int argc, char *argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	Game game(window);
	Menu menu;
	bool display_menu = true;
	while (window.isOpen())
	{
		Crosshair crosshair(10, sf::Color::Red, window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					display_menu = !display_menu;
			}
		}
		if (!display_menu)
		{
			game.GeneralEvent();
			game.CollisionEvent();
			game.Update();
		}
		// menu.Update();
		window.clear();
		window.draw(crosshair);
		if (display_menu)
			window.draw(menu);
		else
			window.draw(game);
		window.display();
	}
	return 0;
}

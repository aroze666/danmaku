#include <SFML/Graphics.hpp>
#include "Game.hpp"
int main (int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(800,800), "SFML works!");
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    Game game(window);
    while(window.isOpen())
    {
	sf::Event event;
	while(window.pollEvent(event))
	{
	    if(event.type == sf::Event::Closed)
		window.close();
	}
	game.GeneralEvent();
	game.CollisionEvent();
	game.Update();
	window.clear();
	window.draw(game);
	window.display();
    }
    return 0;
}

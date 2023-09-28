#include <SFML/Graphics.hpp>
#include "Player.hpp"
int main (int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(800,800), "SFML works!");
    window.setFramerateLimit(30);
    Player box(40,40,10,10);
    while(window.isOpen())
    {
	box.PlayerEvent();
	sf::Event event;
	while(window.pollEvent(event))
	{
	    if(event.type == sf::Event::Closed)
		window.close();
	}
	box.PlayerUpdate();
	window.clear();
	window.draw(box);
	window.display();
    }
    return 0;
}

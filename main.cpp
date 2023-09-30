#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
int main (int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(800,800), "SFML works!");
    window.setFramerateLimit(30);
    Player box({80,40},{10,10});
    Enemy box2({30,30},{10,10});
    while(window.isOpen())
    {
	box.Event();
	sf::Event event;
	while(window.pollEvent(event))
	{
	    if(event.type == sf::Event::Closed)
		window.close();
	}
	box.Update();
	box2.Update();
	window.clear();
	window.draw(box);
	window.draw(box2);
	window.display();
    }
    return 0;
}

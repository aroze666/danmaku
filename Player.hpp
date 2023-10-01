#ifndef __PLAYER__
#define __PLAYER__

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>
class Player : public sf::Drawable
{
	public:
		Player(sf::Vector2f hitbox_size, sf::Vector2f bullet_size);
		void Update();
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(hitbox, states);
			for(auto it=bullet_list.begin(); it!=bullet_list.end(); it++)
				target.draw(*it, states);
		}
		sf::RectangleShape hitbox;
		const sf::Vector2f HITBOX_SIZE;
		const sf::Vector2f BULLET_SIZE;
		std::list<sf::RectangleShape> bullet_list;
};


#endif

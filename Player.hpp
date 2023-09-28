#ifndef __PLAYER__
#define __PLAYER__

#include <SFML/Graphics.hpp>
#include <list>
class Player : public sf::Drawable
{
	public:
		Player(float l_1, float w_1, float l_2, float w_2);
		void PlayerUpdate();
		void PlayerEvent();
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(hit_box, states);
			for(auto it=bullet_list.begin(); it!=bullet_list.end(); it++)
				target.draw(*it, states);
		}
		sf::RectangleShape hit_box;
		const float PLAYER_LENGTH;
		const float PLAYER_WIDTH;
		const float BULLET_LENGTH;
		const float BULLET_WIDTH;
		std::list<sf::RectangleShape> bullet_list;
};


#endif

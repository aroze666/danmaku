#ifndef __GAME__
#define __GAME__
#include "Player.hpp"
#include "Enemy.hpp"
#include "Scene.hpp"
#include <SFML/System/Vector2.hpp>
#include <list>

class Game : public sf::Drawable
{
    public:
        Game(sf::RenderWindow &window);
        void Update();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // target.draw(scene, states);
            target.draw(player, states);
            for(auto it=enemy_list.begin(); it!=enemy_list.end(); it++)
                target.draw(*it, states);
        }
        Player player;
        Scene scene;
        sf::Vector2f window_size;
        std::list<Enemy> enemy_list;
};
#endif

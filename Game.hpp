#ifndef __GAME__
#define __GAME__
#include "Player.hpp"
#include "Enemy.hpp"
#include "Scene.hpp"
#include <list>

class Game : public sf::Drawable
{
    public:
        Game();
        void Update();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(player, states);
        }
    private:
        const sf::Vector2f PLAYER_SIZE;
        const sf::Vector2f PLAYER_BULLET_SIZE;
        const sf::Vector2f ENEMY_SIZE;
        const sf::Vector2f ENEMY_BULLET_SIZE;
        Player player{PLAYER_SIZE, PLAYER_BULLET_SIZE};
        std::list<Enemy> enemy_list;
};
#endif

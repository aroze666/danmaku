#ifndef __GAME__
#define __GAME__
#include "Player.hpp"
#include "Enemy.hpp"
#include "Scene.hpp"
#include "Bullet.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <cmath>
#include <list>

class Game : public sf::Drawable
{
    public:
        Game(sf::RenderWindow &window);
        void Update();
        void GeneralEvent();
        void CollisionEvent();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(scene, states);
            target.draw(player, states);
            int counter = 0;
            for(auto enemy=enemy_list.begin(); enemy!=enemy_list.end(); enemy++)
            {
                counter++;
                target.draw(*enemy, states);
            }
        }
        Player player;
        Scene scene;
        sf::RenderWindow window;
        sf::Clock enemy_respawn_clock;
        int respawn_time;
        sf::Vector2f window_size;
        std::list<Enemy> enemy_list;
        std::list<Bullet> bullet_list;
        bool is_Collide(const sf::Shape &a, const sf::Shape &b);
        void create_Enemy();
};
#endif

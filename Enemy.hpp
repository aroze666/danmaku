#ifndef __ENEMY__
#define __ENEMY__

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>
class Enemy : public sf::Drawable
{
    public:
        Enemy();
        void Update();
        void Event();
        void SetMovementRange(sf::Vector2f range);
        sf::RectangleShape GetHitbox();
        void SetVelocity(sf::Vector2f velocity);
        sf::Vector2f GetVelcoity(){return velocity;}
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(hitbox, states);
        }
        sf::RectangleShape hitbox;
        sf::Vector2f bullet_size;
        sf::Vector2f velocity;
        sf::Vector2f movement_range;
};

#endif

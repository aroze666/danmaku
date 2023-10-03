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
        void SetHit(bool is_hit){this->is_hit = is_hit;}
        bool IsHit(){return is_hit;}
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(hitbox, states);
        }
        bool is_hit;
        sf::RectangleShape hitbox;
        sf::Vector2f bullet_size;
        sf::Vector2f velocity;
        sf::Vector2f movement_range;
};

#endif

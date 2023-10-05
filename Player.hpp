#ifndef __PLAYER__
#define __PLAYER__

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>
#include <iostream>
#include <cmath>
#include "Bullet.hpp"
class Player : public sf::Drawable
{
    public:
        Player();
        void Update();
        void Event();
        void SetHitboxSize(sf::Vector2f size);
        void SetBulletSize(sf::Vector2f size);
        void SetPosition(sf::Vector2f position);
        void SetVelocity(sf::Vector2f velocity);
        bool IsBulletHit(const sf::Shape &object);
        void SetWindow(sf::RenderWindow *window){this->window = window;}
        void SetMovementRange(sf::Vector2f range){movement_range = range;}
        sf::Vector2f GetVelocity(){return velocity;}
        sf::RectangleShape GetHitbox();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(hitbox, states);
            for(auto it=bullet_list.begin(); it!=bullet_list.end(); it++)
                target.draw(*it, states);
        }
        sf::Vector2f terminal_velocity;
        sf::RectangleShape hitbox;
        sf::Vector2f bullet_size;
        std::list<Bullet> bullet_list;
        sf::Vector2f initial_velocity;
        sf::Vector2f velocity;
        sf::Vector2f movement_range;
        sf::RenderWindow *window;
        bool moving;
};


#endif    

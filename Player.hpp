#ifndef __PLAYER__
#define __PLAYER__

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>
class Player : public sf::Drawable
{
    public:
        Player();
        void Update();
        void Event();
        void SetMovementRange(sf::Vector2f range);
        void SetHitboxSize(sf::Vector2f size);
        void SetBulletSize(sf::Vector2f size);
        void SetPosition(sf::Vector2f position);
        void SetVelocity(sf::Vector2f velocity);
        sf::Vector2f GetVelocity(){return velocity;}
        sf::RectangleShape GetHitbox();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(hitbox, states);
            for(auto it=bullet_list.begin(); it!=bullet_list.end(); it++)
                target.draw(*it, states);
        }
        sf::RectangleShape hitbox;
        sf::Vector2f bullet_size;
        std::list<sf::RectangleShape> bullet_list;
        sf::Vector2f velocity;
        sf::Vector2f movement_range;
};


#endif    

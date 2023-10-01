#ifndef __ENEMY__
#define __ENEMY__

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
class Enemy : public sf::Drawable
{
    public:
        Enemy();
        void Update();
        void SetMovementRange(sf::Vector2f range);
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

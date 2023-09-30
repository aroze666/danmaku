#ifndef __ENEMY__
#define __ENEMY__

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
class Enemy : public sf::Drawable
{
public:
    Enemy(sf::Vector2f HITBOX_SIZE, sf::Vector2f BULLET_SIZE);
    void Update();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(hitbox, states);
    }
    sf::RectangleShape hitbox;
    sf::Vector2f HITBOX_SIZE;
    sf::Vector2f BULLET_SIZE;
    sf::Vector2f velocity;
};

#endif

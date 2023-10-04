#ifndef __BULLET__
#define __BULLET__

#include <SFML/Graphics.hpp>
class Bullet : public sf::RectangleShape
{
    public:
        Bullet(){is_hit = false;}
        void Hit(){is_hit = true;}
        bool GetHitStatus(){return is_hit;}
    private:
        bool is_hit;
};

#endif

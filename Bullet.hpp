#ifndef __BULLET__
#define __BULLET__

#include <SFML/Graphics.hpp>
class Bullet : public sf::RectangleShape
{
    public:
        Bullet(){is_hit = false; time=0;}
        void Hit(){is_hit = true;}
        bool GetHitStatus(){return is_hit;}
        void AddTime(){time++;}
        float GetTime(){return time;}
        void SetVelocity(sf::Vector2f velocity){this->velocity = velocity;}
        sf::Vector2f GetVelocity(){return velocity;}
    private:
        sf::Vector2f velocity;
        bool is_hit;
        float time;
};

#endif

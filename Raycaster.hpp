#ifndef __RAYCASTER__
#define __RAYCASTER__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Scene.hpp"
#define grid_size 64
class RayCaster : public sf::Drawable
{
    public:
    RayCaster()
    {
        ray.setFillColor(sf::Color::Magenta);
        // ray.setSize({2,10});
    }
    void Update(sf::Vector2f player_position, sf::Vector2f aim_direction, Scene &scene)
    {
        sf::Vector2f d = {(float)std::sqrt(1+std::pow(aim_direction.y/aim_direction.x,2)), (float)std::sqrt(1+std::pow(aim_direction.x/aim_direction.y,2))};
        sf::Vector2f grid_start = player_position;
        grid_start.x = grid_start.x/64.f;
        grid_start.y = grid_start.y/64.f;
        sf::Vector2i grid_map;
        sf::Vector2i step;
        sf::Vector2f distance;
        grid_map.x = grid_start.x;
        grid_map.y = grid_start.y;
        if(aim_direction.x < 0)
        {
            step.x = -1;
            distance.x = 64*(grid_start.x - (float)grid_map.x)*d.x;
        }else if(aim_direction.x > 0)
        {
            step.x = 1;
            distance.x = 64*((float)(grid_map.x+1) - grid_start.x)*d.x;
        }
        if(aim_direction.y < 0)
        {
            step.y = -1;
            distance.y = 64*(grid_start.y - (float)grid_map.y)*d.y;

        }else if(aim_direction.y >0)
        {
            step.y = 1;
            distance.y = 64*((float)(grid_map.y+1) - grid_start.y)* d.y;
        }
        while(true)
        {
            if(scene.grids[grid_map.y][grid_map.x].wall)
                break;
            if(distance.x > distance.y)
            {
                grid_map.y += step.y;
                if(!scene.grids[grid_map.y][grid_map.x].wall)
                    distance.y += 64*d.y;
            }else{
                grid_map.x += step.x;
                if(!scene.grids[grid_map.y][grid_map.x].wall)
                    distance.x += 64*d.x;
            }
        }
        float angle = 0;
        if(distance.x < distance.y)
            ray.setSize({distance.x, 1});
        else
            ray.setSize({distance.y, 1});
        ray.setPosition(player_position);
        angle = std::atan(aim_direction.y/aim_direction.x)*180/3.1415926;
        if(aim_direction.x < 0)
            angle+=180;
        ray.setRotation(angle);
    }
    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(ray, states);
    }
    sf::RectangleShape ray;
};

#endif

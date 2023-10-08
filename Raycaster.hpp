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
        number_of_rays = 90;
        for(int i = 0; i<number_of_rays;i++)
        {
            sf::RectangleShape new_ray;
            new_ray.setFillColor(sf::Color::Magenta);
            rays.push_back(new_ray);
        }
    }
    void Update(sf::Vector2f position, sf::Vector2f aim_direction, Scene &scene)
    {
        sf::Vector2f direction = aim_direction;
        float angle = std::atan(direction.y/direction.x);
        angle -= 3.1415026/4;
        if(direction.x < 0)
        {
            angle += 3.1415926;
        }
        direction.x = std::cos(angle);
        direction.y = std::sin(angle);
        for(int i = 0; i<rays.size(); i++)
        {
            sf::Vector2f d = {(float)std::sqrt(1+std::pow(direction.y/direction.x,2)), (float)std::sqrt(1+std::pow(direction.x/direction.y,2))};
            sf::Vector2f grid_start = position;
            grid_start.x = grid_start.x/64.f;
            grid_start.y = grid_start.y/64.f;
            sf::Vector2i grid_map;
            sf::Vector2i step;
            sf::Vector2f distance;
            grid_map.x = grid_start.x;
            grid_map.y = grid_start.y;
            if(direction.x < 0)
            {
                step.x = -1;
                distance.x = 64*(grid_start.x - (float)grid_map.x)*d.x;
            }else if(direction.x > 0)
            {
                step.x = 1;
                distance.x = 64*((float)(grid_map.x+1) - grid_start.x)*d.x;
            }
            if(direction.y < 0)
            {
                step.y = -1;
                distance.y = 64*(grid_start.y - (float)grid_map.y)*d.y;

            }else if(direction.y >0)
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

            if(distance.x < distance.y)
                rays[i].setSize({distance.x, 1});
            else
                rays[i].setSize({distance.y, 1});
            rays[i].setPosition(position);
            if(direction.x < 0)
                rays[i].setRotation(180+std::atan(direction.y/direction.x)*180/3.1415926);
            else
                rays[i].setRotation(std::atan(direction.y/direction.x)*180/3.1415926);
            angle += 3.1415026/180;
            direction.x = std::cos(angle);
            direction.y = std::sin(angle);
        }
    }
    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for(int i = 0; i<rays.size(); i++)
            target.draw(rays[i], states);
    }
    int number_of_rays;
    std::vector<sf::RectangleShape> rays;
};

#endif

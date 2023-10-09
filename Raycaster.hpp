#ifndef __RAYCASTER__
#define __RAYCASTER__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Scene.hpp"
#define grid_size 64
#define PI 3.1415926
struct Ray : public sf::RectangleShape
{
    float angle;
    bool direct_hit = false;
};
class RayCaster : public sf::Drawable
{
    public:
    RayCaster(int number)
    {
        number_of_rays = number;
        for(int i = 0; i<number_of_rays;i++)
        {
            Ray new_ray;
            new_ray.setFillColor(sf::Color::Magenta);
            rays.push_back(new_ray);
        }
    }
    void Update(sf::Vector2f position, sf::Vector2f aim_direction, Scene &scene)
    {
        sf::Vector2f direction = aim_direction;
        float angle = std::atan(direction.y/direction.x);
        if(direction.x < 0)
        {
            angle += PI;
        }
        player_angle = angle;
        angle -= ((float)number_of_rays)/2*PI/180;
        direction.x = std::cos(angle);
        direction.y = std::sin(angle);
        for(int i = 0; i<rays.size(); i++)
        {
            rays[i].angle = angle;
            sf::Vector2f d = {(float)std::sqrt(1+std::pow(direction.y/direction.x,2)), (float)std::sqrt(1+std::pow(direction.x/direction.y,2))};
            sf::Vector2f grid_start = position;
            grid_start.x = grid_start.x/grid_size;
            grid_start.y = grid_start.y/grid_size;
            sf::Vector2i grid_map;
            sf::Vector2i step;
            sf::Vector2f distance;
            grid_map.x = grid_start.x;
            grid_map.y = grid_start.y;
            if(direction.x < 0)
            {
                step.x = -1;
                distance.x = grid_size*(grid_start.x - (float)grid_map.x)*d.x;
            }else if(direction.x > 0)
            {
                step.x = 1;
                distance.x = grid_size*((float)(grid_map.x+1) - grid_start.x)*d.x;
            }
            if(direction.y < 0)
            {
                step.y = -1;
                distance.y = grid_size*(grid_start.y - (float)grid_map.y)*d.y;

            }else if(direction.y >0)
            {
                step.y = 1;
                distance.y = grid_size*((float)(grid_map.y+1) - grid_start.y)* d.y;
            }
            while(true)
            {
                if(scene.grids[grid_map.y][grid_map.x].wall)
                    break;
                if(distance.x > distance.y)
                {
                    grid_map.y += step.y;
                    if(!scene.grids[grid_map.y][grid_map.x].wall)
                        distance.y += grid_size*d.y;
                }else{
                    grid_map.x += step.x;
                    if(!scene.grids[grid_map.y][grid_map.x].wall)
                        distance.x += grid_size*d.x;
                }
            }
            if(distance.x < distance.y)
            {
                rays[i].setSize({distance.x, 1});
                rays[i].direct_hit = false;
            }
            else
            {
                rays[i].setSize({distance.y, 1});
                rays[i].direct_hit = true;
            }
            rays[i].setPosition(position);
            if(direction.x < 0)
                rays[i].setRotation(180+std::atan(direction.y/direction.x)*180/PI);
            else
                rays[i].setRotation(std::atan(direction.y/direction.x)*180/PI);
            angle += PI/180; 
            direction.x = std::cos(angle);
            direction.y = std::sin(angle);
        }
    }
    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for(int i = 0; i<rays.size(); i++)
        {
            sf::RectangleShape box;
            if(rays[i].direct_hit)
                box.setFillColor(sf::Color(255,255,255,255));
            else
                box.setFillColor(sf::Color(180,180,180,255));
            float line_height = 64*512/rays[i].getSize().x/std::cos(player_angle - rays[i].angle);
            box.setPosition({0+8.f*i, 1024-line_height/2 - 256});
            box.setSize({8, line_height});
            target.draw(box, states);
            target.draw(rays[i], states);
        }
    }
    float player_angle;
    int number_of_rays;
    std::vector<Ray> rays;
};

#endif

#ifndef __SCENE__
#define __SCENE__
#include <SFML/Graphics.hpp>
#include <vector>
struct Grid : public sf::RectangleShape
{
    bool wall = false;
};
class Scene : public sf::Drawable
{
    public:
        Scene();
        Scene(int *map);
        void Update();
        sf::Vector2f scene_size = {512,512};
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            
            for(auto i=grids.begin(); i!=grids.end();i++)
                target.draw(*i, states);
        }
        int *map;
        std::vector<Grid> grids;
};

#endif

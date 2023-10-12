#ifndef __MENU__
#define __MENU__
#include <SFML/Graphics.hpp>
class Menu : public sf::Drawable
{
public:
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        // target.draw(scene, states);
    }
};

#endif
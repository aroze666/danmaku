#ifndef __CROSSHAIR__
#define __CROSSHAIR__
#include <SFML/Graphics.hpp>
class Crosshair : public sf::Drawable
{
public:
    Crosshair(float radius, sf::Color color, sf::RenderWindow &window)
    {
        crosshair.setRadius(radius);
        crosshair.setFillColor(color);
        crosshair.setPosition({sf::Mouse::getPosition(window).x - radius, sf::Mouse::getPosition(window).y - radius});
    }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(crosshair, states);
    }
    sf::CircleShape crosshair;
};

#endif
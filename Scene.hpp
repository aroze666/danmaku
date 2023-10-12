#ifndef __SCENE__
#define __SCENE__
#include <SFML/Graphics.hpp>
class Scene : public sf::Drawable
{
public:
    Scene();
    void Update();

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(background, states);
        for (sf::CircleShape meteor : meteors)
            target.draw(meteor, states);
    }
    sf::RectangleShape background;
    sf::CircleShape meteors[5];
};

#endif

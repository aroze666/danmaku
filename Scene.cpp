#include "Scene.hpp"

Scene::Scene()
{
    background.setFillColor(sf::Color::Blue);
    for (sf::CircleShape meteor : meteors)
    {
        meteor.setFillColor(sf::Color::Cyan);
        meteor.setRadius(20);
    }
}

void Scene::Update()
{
}

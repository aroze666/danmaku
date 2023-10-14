#ifndef __MENU__
#define __MENU__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
class Button : public sf::Drawable
{
public:
    Button(std::string name)
    {
        if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf"))
        {
            std::cout << "Error loading fonts.\n";
        }
        else
        {
            button.setFillColor(sf::Color::White);
            text.setFont(font);
            text.setString(name);
            text.setFillColor(sf::Color::Red);
        }
        text.setScale({2, 2});
        button.setPosition(400, 400);
        text.setPosition(400 - text.getGlobalBounds().width / 2, 400 - text.getGlobalBounds().height / 2);
    }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(button, states);
        target.draw(text, states);
    }
    sf::RectangleShape button;
    sf::Font font;
    sf::Text text;
};
class Menu : public sf::Drawable
{
public:
    Menu()
    {
    }
    void Update();

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(start, states);
    }
    Button start{"PAUSED"};
};

#endif
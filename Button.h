#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button 
{
public:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color clickColor;
    bool isClicked;

    Button(float width, float height, const string& label, sf::Font& font): 
        isClicked(false), 
        idleColor(sf::Color(30, 30, 30)), 
        hoverColor(sf::Color(60, 60, 60)), 
        clickColor(sf::Color(90, 90, 90)) 

    {
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(idleColor);
        shape.setOutlineThickness(1.f);
        shape.setOutlineColor(sf::Color::White);

        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(shape.getPosition().x + 10, shape.getPosition().y + 10);
    }

    void setPosition(float x, float y) 
    {
        shape.setPosition(x, y);
        text.setPosition(x + 10, y + 10);
    }

    void draw(sf::RenderWindow& window) 
    {
        window.draw(shape);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow& window) 
    {
        sf::FloatRect bounds = shape.getGlobalBounds();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return bounds.contains(static_cast<sf::Vector2f>(mousePos));
    }

    void update(sf::RenderWindow& window) 
    {
        if (isMouseOver(window)) 
        {
            shape.setFillColor(hoverColor);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
            {
                shape.setFillColor(clickColor);
                isClicked = true;
            }

            else 
            {
                isClicked = false;
            }
        }

        else 
        {
            shape.setFillColor(idleColor);
        }
    }

    bool isClickedFunc() 
    {
        return isClicked;
    }
};

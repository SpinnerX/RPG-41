#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class GameCharacter{
public:
    GameCharacter() = default;

    virtual ~GameCharacter() { delete texture; }

    virtual sf::FloatRect getBoundaries() = 0;

    virtual void draw(sf::RenderWindow* window) = 0;

protected:
    sf::RectangleShape bodyShape;
    sf::Texture* texture;
    sf::Vector2f position;

};
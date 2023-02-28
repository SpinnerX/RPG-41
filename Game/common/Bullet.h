#include <SFML/Graphics.hpp>
#include "common/KeyboardEvents.h"

class Bullet {
public:
    Bullet(sf::Texture *texture, sf::Vector2f pos) {
        this->shape.setTexture(*texture);
        // this->shape.setScale();
        this->shape.setPosition(pos);
    }

private:
    sf::Sprite shape;
};
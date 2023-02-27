#include <SFML/Graphics.hpp>
#include "common/KeyboardEvents.h"

class Bullet {
    public:
        sf::Sprite shape;

    Bullet(sf::Texture *texture, sf::Vector2f pos) {
        this->shape.setTexture(*texture);
        // this->shape.setScale();
        this->shape.setPosition(pos);
    }
};
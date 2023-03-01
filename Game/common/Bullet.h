#include <SFML/Graphics.hpp>
#include "common/KeyboardEvents.h"

class Bullet {
public:
    Bullet(){}
    Bullet(sf::Texture *texture, sf::Vector2f pos) {
        this->shape.setTexture(*texture);
        this->shape.setPosition(pos);
    }

    Bullet(float x, float y, std::string filename){
        if(!texture.loadFromFile(filename)) return;

        shape.setTexture(texture);
        shape.setPosition(x, y);
    }

    void update(float x, float y){
        shape.setPosition(x, y);
    }

    void draw(sf::RenderWindow* window){
        window->draw(shape);
    }

private:
    sf::Sprite shape;
    sf::Texture texture;
};
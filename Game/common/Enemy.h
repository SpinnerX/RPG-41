#include <SFML/Graphics.hpp>

class Enemy {
public:
    sf::Sprite shape;
    sf::Texture texture;
    sf::Vector2f position;

    Enemy() {
        std::string filename = "Game/assets/rocket-texture.png";
        
        if(!texture.loadFromFile(filename)) return;
        this->shape.setTexture(texture);
        this->shape.setScale(0.1f,0.1f);
        this->shape.setPosition(300.f, 300.f);
    }

    void updatePosition() {
        this->shape.move(20.f, 0.f);
    }

    void draw(sf::RenderWindow* window){
        window->draw(shape);
    }
};
#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Player {
public:
    sf::Sprite shape;
    sf::Texture texture;
    sf::Vector2f position;
    std::vector<Bullet> bullets;

    Player() {
        std::string filename = "Game/assets/rocket-texture.png";
        
        /**
         * @brief 
         Window Dimensions
         window->getSize().x = width
         window->getSize().y = height
         
         * 
         */
        if(!texture.loadFromFile(filename)) return;
        this->shape.setTexture(texture);
        this->shape.setScale(0.1f,0.1f);
        this->shape.setPosition(300.f, 300.f);
        //this->shape.setScale(0.1f, 0.1f);
        //this->shape.setOrigin(-120.0, -120.0);
    }

    void updatePosition(KeyState state) {
        if(state.aPressed) this->shape.move(-10.f, 0.f);
        if(state.dPressed) this->shape.move(10.f, 0.f);
    }

    void draw(sf::RenderWindow* window){
        window->draw(shape);
    }
};
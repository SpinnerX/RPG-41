#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy() {
        std::string filename = "Game/assets/enemyDefault.png";
        
        if(!texture.loadFromFile(filename)) return;
        shape.setTexture(texture);
        shape.setScale(0.75f,0.75f);
        shape.setPosition(300.f, 300.f);
    }

    Enemy(float x, float y, std::string filename){
        
        if(!texture.loadFromFile(filename)) return;
        shape.setTexture(texture);
        // this->shape.setScale(0.1f,0.1f); // This is the original value that we set it too.
        shape.setScale(0.4f, 0.4f); // Testing enemy location and scaling.
        shape.setPosition(x, y);
    }

    void update(float x, float y){
        shape.move(x, y);
    }

    sf::Vector2f getPosition() const { return shape.getPosition(); }

    void draw(sf::RenderWindow* window){
        window->draw(shape);
    }

private:
    sf::Sprite shape;
    sf::RectangleShape bodyShape;
    sf::Texture texture;
    sf::Vector2f position;
};
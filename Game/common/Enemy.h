#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy() {
        std::string filename = "Game/assets/enemyDefault.png";

        texture = new sf::Texture();
        if(!texture->loadFromFile(filename)) return;

        bodyShape = sf::RectangleShape(sf::Vector2f(10.0f, 15.0f)); // This is how we get rectangle drawn onto the screen.
        bodyShape.setTexture(texture);
        bodyShape.setScale(0.75f,0.75f);
        bodyShape.setPosition(300.f, 300.f);
    }

    Enemy(float x, float y, std::string filename){
        texture = new sf::Texture();
        if(!texture->loadFromFile(filename)) return;

        bodyShape = sf::RectangleShape(sf::Vector2f(50.0f, 50.0f)); // This is how we get rectangle drawn onto the screen.
        bodyShape.setTexture(texture);
        // this->shape.setScale(0.1f,0.1f); // This is the original value that we set it too.
        bodyShape.setScale(0.4f, 0.4f); // Testing enemy location and scaling.
        bodyShape.setPosition(x, y);
    }

    // This is what animates the enemy movements.
    void update(float x, float y){
        bodyShape.move(x, y);
    }

    sf::FloatRect getBoundaries() { return bodyShape.getGlobalBounds(); }

    sf::Vector2f getPosition() const { return bodyShape.getPosition(); }

    void draw(sf::RenderWindow* window){
        window->draw(bodyShape);
    }

private:
    sf::RectangleShape enemyBodyShape;
    sf::RectangleShape bodyShape;
    sf::Texture* texture;
    sf::Vector2f position;
};
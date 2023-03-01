#include <SFML/Graphics.hpp>
#include "common/KeyboardEvents.h"

class Bullet {
public:
    Bullet(){}
    Bullet(sf::Texture *texture, sf::Vector2f pos) {
        bulletBody.setTexture(texture);
        bulletBody.setPosition(pos);
    }

    Bullet(float x, float y, std::string filename){
        texture = new sf::Texture();
        if(!texture->loadFromFile(filename)) return;

        bulletBody = sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
        bulletBody.setTexture(texture);
        bulletBody.setPosition(x, y);
    }

    // Each bullet will check if we hit an enemy
    // Example: bullets[i].hit(enemy[i]);
    bool hit(sf::FloatRect otherBounds) { return bulletBody.getGlobalBounds().intersects(otherBounds); }

    void update(float x, float y){
        bulletBody.move(x, y);
    }

    void draw(sf::RenderWindow* window){
        window->draw(bulletBody);
    }

private:
    // sf::Sprite shape;
    sf::RectangleShape bulletBody;
    sf::Texture* texture;
};
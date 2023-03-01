#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Enemy.h"

class Player{
public:
    Player(){
        std::string filename = "Game/assets/ship1.png";
        sf::Texture* texture = new sf::Texture();
        if(!texture->loadFromFile(filename)) return;

        bodyShape = sf::RectangleShape(sf::Vector2f(10.0f, 10.0f)); // This is how we get rectangle drawn onto the screen.
        bodyShape.setTexture(texture);
        bodyShape.setScale(10.0f, 10.0f);
        bodyShape.setPosition(300.f, 300.f);
        bullets = std::vector<Bullet *>();
    }

    void update(KeyState state) {
        if(state.wPressed) bodyShape.move(0.0f, -10.0f);
        if(state.aPressed) bodyShape.move(-10.f, 0.f);
        if(state.dPressed) bodyShape.move(10.f, 0.f);
        if(state.sPressed) bodyShape.move(0.0f, 10.0f);
        if(state.spacePressed) shoot();
    }

    void shoot(){
        std::cout << "Shooting bullets function called!\n";
        bullets.push_back(new Bullet(bodyShape.getPosition().x, bodyShape.getPosition().y, "Game/assets/bullet.png"));
    }

    // Handling collision for the enemies.
    void collision(std::vector<Enemy *>& enemies){
        if(!enemies.empty() && !bullets.empty()){
            for(size_t i = 0; i < bullets.size(); i++){
                for(size_t j = 0; j < enemies.size(); j++){
                    if(bullets[i]->hit(enemies[j]->getBoundaries())){
                        bullets.erase(bullets.begin() + i);
                        enemies.erase(enemies.begin() + j);
                        return;
                    }
                }
            }
        }
    }

    void renderBullets(sf::RenderWindow* window){
        for(size_t i = 0; i < bullets.size(); i++) bullets[i]->update(0.0, -0.5);

        // rendering and drawing the bullets.
        for(size_t i = 0; i < bullets.size(); i++) bullets[i]->draw(window);
    }

    void draw(sf::RenderWindow* window){
        window->draw(bodyShape);
    }

private:
    sf::RectangleShape bodyShape;
    sf::Vector2f position;

    std::vector<Bullet *> bullets;

    int enemiesIndex; // Locating which index of the enemy we are hitting with our bullet projectiles.
    unsigned long maxAmmo;

};
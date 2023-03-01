#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Player {
public:


    Player() {
        std::string filename = "Game/assets/ship1.png";
        
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

    void update(KeyState state) {
        if(state.wPressed) shape.move(0.0f, -10.0f);
        if(state.aPressed) shape.move(-10.f, 0.f);
        if(state.dPressed) shape.move(10.f, 0.f);
        if(state.sPressed) shape.move(0.0f, 10.0f);
        if(state.spacePressed) shoot();
    }

    void shoot(){
        bullets = std::vector<Bullet *>();
        std::cout << "Shooting bullets function called!\n";
        maxAmmo = 500;
        for(size_t i = 0; i < maxAmmo; i++){
            bullets.push_back(new Bullet(300.0f, 300.0f, "Game/assets/bullet.png"));
        }
    }

    void update(float x, float y){
        for(size_t i = 0; i < bullets.size(); i++) bullets[i]->update(x, y);
    }

    void renderBullets(sf::RenderWindow* window){

        // rendering and drawing the bullets.
        for(size_t i = 0; i < bullets.size(); i++) bullets[i]->draw(window);
    }

    void draw(sf::RenderWindow* window){
        window->draw(shape);
    }

private:
    sf::Sprite shape;
    sf::Texture texture;
    sf::Vector2f position;
    std::vector<Bullet *> bullets;

    unsigned long maxAmmo;
};
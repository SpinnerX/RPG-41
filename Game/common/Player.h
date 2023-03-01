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

        initBullets();
        bulletID = 0;
        
    }

    ~Player(){
        for(size_t i = 0; i < bullets.size(); i++) delete bullets[i];
    }

    void update(KeyState state, std::vector<Enemy *>& enemies) {
        if(state.wPressed) bodyShape.move(0.0f, -10.0f);
        if(state.aPressed) bodyShape.move(-10.f, 0.f);
        if(state.dPressed) bodyShape.move(10.f, 0.f);
        if(state.sPressed) bodyShape.move(0.0f, 10.0f);
        // if(state.spacePressed) initBullets(); // Creating and allocating these bullets

        // This is so we can render each bullet we shoot for everytime we press the space button.
        if(state.spacePressed){
            bulletID += 1;
        }
    }

    /**
     * @brief 
     * 
     * Initially this is what creates the bullets, when we press the space button.
     * 
     */
    void initBullets(){
        bullets = std::vector<Bullet *>();
        std::cout << "Shooting bullets function called!\n";
        maxAmmo = 500;
        for(size_t i = 0; i < maxAmmo; i++) bullets.push_back(new Bullet(bodyShape.getPosition().x, bodyShape.getPosition().y, "Game/assets/bullet.png"));
    }

    /**
     * @brief 
     * 
     * This is still pretty buggy, just figuring out how to do collision based on the boundaries of the enemies and the bullets. (Still in progress)
     * 
     * @param x 
     * @param y 
     * @param enemies 
     */
    void update(float x, float y, std::vector<Enemy *>& enemies){
        // for(size_t i = 0; i < bullets.size(); i++) bullets[i]->update(x, y);
        for(size_t i = 0; i < bullets.size(); i++){
            bullets[i]->update(x, y);

            for(size_t i = 0; i < enemies.size(); i++){
                if(bullets[i]->hit(enemies[i]->getBoundaries())){
                    std::cout << "Enemy Hit!\n";
                    enemies.erase(enemies.begin() + i);
                }
            }
        }
    }

    void renderBullets(sf::RenderWindow* window){
        // for(size_t i = 0; i < bullets.size(); i++) bullets[i]->update(0.0, -0.5);

        // rendering and drawing the bullets.
        // for(size_t i = 0; i < bullets.size(); i++) bullets[i]->draw(window);

        bullets[bulletID]->update(0.0f, -0.2f);
        bullets[bulletID]->draw(window);
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

    int bulletID;

};
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Enemy.h"
#include "SoundFX.h"
#include "GameState.h"

class Player : public GameCharacter{
public:
    Player(int aliveCount) : GameCharacter() {
        std::string filename = "Game/assets/ship1.png";
        texture = new sf::Texture();
        if(!texture->loadFromFile(filename)) return;

        bodyShape = sf::RectangleShape(sf::Vector2f(10.0f, 10.0f)); // This is how we get rectangle drawn onto the screen.
        bodyShape.setTexture(texture);
        bodyShape.setScale(10.0f, 10.0f);
        bodyShape.setPosition(300.f, 300.f);
        bullets = std::vector<Bullet *>();
        enemiesAlive = aliveCount;
    }

    void update(KeyState state) {
        if(state.wPressed) bodyShape.move(0.0f, -10.0f);
        if(state.aPressed) bodyShape.move(-10.f, 0.f);
        if(state.dPressed) bodyShape.move(10.f, 0.f);
        if(state.sPressed) bodyShape.move(0.0f, 10.0f);
        if(state.spacePressed) shoot();
    }

    void update (float x, float y) override {}

    void shoot(){
        std::cout << "Shooting bullets function called!\n";
        bullets.push_back(new Bullet(bodyShape.getPosition().x, bodyShape.getPosition().y, "Game/assets/bullet.png"));
    }

    void moveLeftX(){
        bodyShape.move(-10.0f, 0.0f);
    }
    void moveRightX(){
        bodyShape.move(10.f, 0.0);
    }
    void moveUpY(){
        bodyShape.move(0.0f, -10.0f);
    }
    void moveDownY(){
        bodyShape.move(0.0f, 10.0f);
    }

    sf::FloatRect getBoundaries() override { return bodyShape.getGlobalBounds(); }
    
    //get X
    sf::Vector2f getPosition() override { return bodyShape.getPosition(); }

    //get Y
    //float getPosY() { return bodyShape.getPosition().y; }
    
    // Handling collision for the enemies.
    void collision(std::vector<GameCharacter *>& enemies){
        if(!enemies.empty() && !bullets.empty()){
            for(size_t i = 0; i < bullets.size(); i++){
                for(size_t j = 0; j < enemies.size(); j++){
                    if(bullets[i]->hit(enemies[j]->getBoundaries())){
                        bullets.erase(bullets.begin() + i);
                        enemies.erase(enemies.begin() + j);
                        sounds.playSound(4);
                        score += 1;
                        enemiesAlive -= 1; // decrement everytime an enemy dies.
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

    bool allEnemiesDied() const { return (enemiesAlive == 0); }

    void draw(sf::RenderWindow* window) override {
        window->draw(bodyShape);
    }

    int getScore() {
        return score;
    }

private:

    std::vector<Bullet *> bullets;

    int enemiesIndex; // Locating which index of the enemy we are hitting with our bullet projectiles.
    unsigned long maxAmmo;



    int enemiesAlive;
    int score;


    SoundFX sounds;

};
#pragma once
#include <iostream>
#include "common/KeyboardEvents.h"
#include "common/Player.h"
// #include "common/Enemy.h"
#include "common/ButtonOld.h"
#include <vector>
#include <unistd.h>

/**
 * @brief 
 * 
 * GameState Class
 * 
 * This is what is going to change state of the game from the menu screen to the actual game.
 * 
 */

class GameState{
public:
    GameState(unsigned int w, unsigned int h, const std::string& title, uint32_t style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings()){
        width = w;
        height = h;
        this->title = title;

        enemies = std::vector<Enemy *>();

        maxEnemies = 4;
        for(size_t i = 0; i < maxEnemies; i++) enemies.push_back(new Enemy(i * 100, 100, "Game/assets/enemyDefault.png"));
    }

    ~GameState(){
        for(size_t i = 0; i < enemies.size(); i++) delete enemies[i];
        delete window;
    }

    void begin(){
        // Creates a new window everytime we leave and come back to it.
        window = new sf::RenderWindow();
        window->create(sf::VideoMode(width, height), title);

        events = new KeyboardInputHandler(window);

        initEnemies(); // Spawn enemies, everytime this window opens up.

        window->setVisible(true);
        window->draw(backgroundSprite);

        player.draw(window);

        window->draw(backgroundSprite);

        window->display();

        while(window->isOpen()){
            // Handle the fps
            sf::Clock clock;
            float Framerate = 100.f / clock.getElapsedTime().asSeconds();
            
            events->listener();
            
            if(events->windowShouldClose()){
                window->setVisible(false);
                return;
            }

            state();

            events->reset();
            clock.restart();
        }
    }

    void generateBackground(sf::Sprite& bg){ backgroundSprite = bg; }

private:
    void state(){
        player.update(events->state()); // Allowing the player for movements

        //Render
        window->clear();
        window->draw(backgroundSprite);
        
        // Updating enemies movements.
        // for(Enemy* enemy : enemies) enemy->update(0.1f, 0.f);

        for(int i = 0; i < enemies.size(); i++){
            enemies[i]->update(0.1f, 0.f);
        }

        // for(Enemy* enemy : enemies) enemy->draw(window);
        for(int i = 0; i < enemies.size(); i++){
            enemies[i]->draw(window);
        }
        
        player.draw(window);

        player.renderBullets(window);

        window->display();
    }

private:
    void initEnemies(){
        enemies = std::vector<Enemy *>();

        maxEnemies = 4;
        for(size_t i = 0; i < maxEnemies; i++) enemies.push_back(new Enemy(i * 100, 100, "Game/assets/enemyDefault.png"));
    }

    // Removing enemies based on their given location and by index.
    void removeEnemy(int index){
        // The index is how many moves the enemy made to remove that enemy
        enemies.erase(enemies.begin() + index); // This is whats going to remove the enemy
    }

    // This should return an index of the enemy we hit.
    int hit(){

    }

private:
    sf::RenderWindow* window;
    KeyboardInputHandler* events;

    Player player;

    int maxEnemies; // Max of enemies to spawn.
    int enemyAlive; // Keeping track of the count of enemies alive in this current game.
    int enemySpawnTimer;
    float enemySpawnMaxTimer;


    // Enemy enemy;
    std::vector<Enemy *> enemies;
    


    sf::Sprite backgroundSprite;

private:
    unsigned int width, height;
    std::string title;
};
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
    }

    virtual ~GameState(){
        for(size_t i = 0; i < enemies.size(); i++) delete enemies[i];
        delete window;
    }

    void begin(){
        // Creates a new window everytime we leave and come back to it.
        window = new sf::RenderWindow();
        window->create(sf::VideoMode(width, height), title);

        events = new KeyboardInputHandler(window);

        

        // This allows us to reset the enemies original position everytime we go back to this function call.
        enemies = std::vector<GameCharacter *>();

        
        maxEnemies = 4;
        for(size_t i = 0; i < maxEnemies; i++) enemies.push_back(new Enemy(i * 100, 100, "Game/assets/enemyDefault.png"));

        player = new Player(maxEnemies);
        

        window->setVisible(true);
        window->draw(backgroundSprite);

        player->draw(window);

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
        player->update(events->state()); // Allowing the player for movements

        //Render
        window->clear();
        window->draw(backgroundSprite);

        float x = 0.1f;
        float y = 0.0f;
        // Updates the movements of the enemies
        for(const GameCharacter* enemy : enemies){
            /**
             * @brief 
             TODO: Debug and fix the movement
             So, the enemy can move to the right, then when the enemy hits the right side of window
             the enemy can bounce back and hit the left side of the window and move to the right-side, initially.

             This is a bug, that we need help fixing...
             * 
             */
            // enemy->update(x, y);

        }

        player->collision(enemies);


        for(GameCharacter* enemy : enemies) enemy->draw(window);
        
        player->draw(window);

        player->renderBullets(window);

        window->display();
    }

private:
    sf::RenderWindow* window;
    KeyboardInputHandler* events;

    Player* player;

    int maxEnemies; // Max of enemies to spawn.
    int enemyAlive; // Keeping track of the count of enemies alive in this current game.
    int enemySpawnTimer;
    float enemySpawnMaxTimer;


    // Enemy enemy;
    std::vector<GameCharacter *> enemies;
    


    sf::Sprite backgroundSprite;

private:
    unsigned int width, height;
    std::string title;

    SoundFX startGameSound;
};
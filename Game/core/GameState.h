#pragma once
#include <iostream>
#include "common/KeyboardEvents.h"
#include "common/Player.h"
#include "common/Enemy.h"
#include "common/ButtonOld.h"

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

    ~GameState(){ delete window; }

    void begin(){
        // Creates a new window everytime we leave and come back to it.
        window = new sf::RenderWindow();
        window->create(sf::VideoMode(width, height), title);

        events = new KeyboardInputHandler(window);

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
        player.updatePosition(events->state());
        enemy.updatePosition();

        //Render
        window->clear();
        player.draw(window);
        enemy.draw(window);
        window->display();
    }

private:
    sf::RenderWindow* window;
    KeyboardInputHandler* events;

    Player player;
    Enemy enemy;


    sf::Sprite backgroundSprite;

private:
    unsigned int width, height;
    std::string title;
};
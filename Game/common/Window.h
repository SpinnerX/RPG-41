#pragma once
#include <iostream>
#include "KeyboardEvents.h"
#include "Player.h"
#include "Enemy.h"
// #include "Button.h"
#include "ButtonOld.h"
/**
 * @brief 
 * Window.h
 * 
 * - This class will handle anything happening to the window and rendering objects into the world
 * Which allows us to do more then one thing instead of relying all our code to be used in main.
 * 
 * This is to encapsulate how the code base will be.
 * 
 * https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Image.php
 */

class Window {
public:
    // Allows us to create the window a lot easier, and for some reason get an implicit/explicit error, so we turn it into a pointer to work around that.
    // Then we allocate memory, but delete it using the destructor
    Window(unsigned int w, unsigned int h, const std::string& title, uint32_t style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings()){
        window = new sf::RenderWindow();
        window->create(sf::VideoMode(w, h), title, style, settings); // instead of using the constructor where we pass in the parameters, we instead use the function .create from RenderWindow(..) to create our window instead.
        events = new KeyboardInputHandler(window); // Going to be handling the key events, and the state of our entire program.
    }
    
    ~Window(){
        delete window;
    }

    /**
     * @brief 
     * Mainloop will run our entire application, just to make things easier for us to debug.
     * 
     */

    void mainloop(){

        sf::Texture background;
        std::string filename = "Game/assets/image.png";
        if(!background.loadFromFile(filename)) return;

        sf::Sprite bgSprite(background);
        // This "should" allow us to scale the image to the entire screen.
        bgSprite.setScale(window->getSize().x/bgSprite.getLocalBounds().width, window->getSize().y/bgSprite.getLocalBounds().height);

        // DO NOT ADJUST JUST YET.... this code works lol
        sf::Font font;
        std::string fontFilename = "Game/assets/fonts/space_invaders.ttf";
        if (!font.loadFromFile(fontFilename)) return;
        sf::Text text("CODE INVADERS", font, 50);
        text.setOrigin(-75.0, -125.0);
        
        sf::Text enterText("Press Enter To Continue:", font, 25);
        enterText.setOrigin(-100.0, -200.0);
        /*if (events->userEnter()) {
            window->clear();
            window->setVisible(false);
            playerWindow->setVisible(true);
            playerWindow->display();
        }*/
        
        // This is the game mainloop.
        // Any gamestate can now be utilized in their own respective functions.
        while(window->isOpen()){
            // sf::Event event;
            events->listener(); // Listening for user key inputs.

            // Beyond this point, you call the gamestate().

            if(events->userEnter()){
                window->clear();
                window->setVisible(false);
                start(bgSprite);
            }

            events->reset();

            
            window->draw(bgSprite);
            window->draw(text);
            window->draw(enterText);
            window->display();
        }
    }

    void start(sf::Sprite bgSprite){
        playerWindow = new sf::RenderWindow(sf::VideoMode(window->getSize().x, window->getSize().y), "Player Window");
        playerWindow->setVisible(true);
        playerWindow->draw(bgSprite);

        events = new KeyboardInputHandler(playerWindow);

        player.draw(playerWindow);

        playerWindow->display();

        while(playerWindow->isOpen()){
            sf::Clock clock;
            float Framerate = 100.f / clock.getElapsedTime().asSeconds();
            
            events->listener();
            
            if(events->windowShouldClose()) playerWindow->close();
            gamestate();

            events->reset();

            clock.restart();
        }

    }

    void gamestate() {

        player.updatePosition(events->state());
        enemy.updatePosition();

        //Render
        playerWindow->clear();
        player.draw(playerWindow);
        enemy.draw(playerWindow);
        playerWindow->display();
    }

private:
    sf::RenderWindow* window;
    sf::RenderWindow* playerWindow;
    KeyboardInputHandler* events;
    Player player;
    Enemy enemy;
};
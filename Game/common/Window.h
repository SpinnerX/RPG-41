#pragma once
#include <iostream>
#include "KeyboardEvents.h"

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

class Window{
public:
    // Allows us to create the window a lot easier, and for some reason get an implicit/explicit error, so we turn it into a pointer to work around that.
    // Then we allocate memory, but delete it using the destructor
    Window(unsigned int w, unsigned int h, const std::string& title, uint32_t style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings()){
        window = new sf::RenderWindow();
        window->create(sf::VideoMode(w, h), title, style, settings); // instead of using the constructor where we pass in the parameters, we instead use the function .create from RenderWindow(..) to create our window instead.

        events = new KeyboardInputHandler(window); // Going to be handling the key events, and the state of our entire program.
    }
    
    ~Window(){ delete window; }

    /**
     * @brief 
     * Mainloop will run our entire application, just to make things easier for us to debug.
     * 
     */
    void mainloop(){
        // This while loop says (as long the window is opened, then we display the window.)
        // Then after clicking the escape key we window->close(); which closes the window.

        sf::Texture background;
        std::string filename = "Game/assets/backgroundTest.jpg";
        if(!background.loadFromFile(filename)) return;

        sf::Sprite bgSprite(background);
        bgSprite.setTexture(background);

        while(window->isOpen()){
            events->startEvents();
            

            if(events->windowShouldClose()) window->close();

            if(events->forward()) std::cout << "W key has been pressed!\n";

            events->reset();

            window->clear();
            window->draw(bgSprite);
            window->display();
        }
    }

private:
    sf::RenderWindow* window;
    KeyboardInputHandler* events;
};
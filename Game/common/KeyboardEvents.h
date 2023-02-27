#pragma once
#include <SFML/Graphics.hpp>


/**
 * @brief 
 * stateClose - the state if the window should close, should be default to false so it does not close. Only true will window close.
 * 
 * 
 * - Might have variables representing different states in this class, allowing us to help handle how we may want to maneuver 
 */

struct KeyState{
        KeyState(){
            stateClose = false; // window state to close.

            // Variables indicating when we press WASD (for movements, this is just because our ideas will involve movement animations.)
            wPressed = false;
            aPressed = false;
            sPressed = false;
            dPressed = false;
            enterPressed = false;
        }
        
        // reset these to default values, so when we click and release it switches the values for example like ON/OFF states.
    void reset(){
            wPressed = false;
            aPressed = false;
            sPressed = false;
            dPressed = false;
            enterPressed = false; 
    }
        
    bool stateClose; // window state to close.

    bool wPressed;
    bool aPressed;
    bool sPressed;
    bool dPressed;
    bool enterPressed;
};


class KeyboardInputHandler{
    
public:
    KeyboardInputHandler(sf::RenderWindow* _window) : window(_window){}

    ~KeyboardInputHandler(){
        reset();
        delete window;
    }


    // Listener for key events.
    void listener(){
        while(window->pollEvent(event)){
            
            // Close window when we press escape.
            if(event.key.code == sf::Keyboard::Escape) {
                std::cout << "Escape Pressed\n";
                keyMovements.stateClose = true;
                return;
            }

            // If we click any related key we press we switch the state to true.
            if(event.key.code == sf::Keyboard::W) {
                std::cout << "W Pressed!\n";
                keyMovements.wPressed = true;
            }

            if(event.key.code == sf::Keyboard::A) {
                //std::cout << "A Pressed!\n";
                keyMovements.aPressed = true;
            }

            if(event.key.code == sf::Keyboard::D) {
                //std::cout << "D Pressed!\n";
                keyMovements.dPressed = true;
            }

            if (event.key.code == sf::Keyboard::Enter) {
                std::cout << "Enter Pressed\n";
                keyMovements.enterPressed = true;
            }
        }
    }
    KeyState state() const { return keyMovements; }
    // Allow us to make function calls to make it easier to know what functions to call to allow for flexibility.
    bool forward() const{ return keyMovements.wPressed; }
    bool userEnter() const {return keyMovements.enterPressed; }

    void reset(){ keyMovements.reset(); }

    bool windowShouldClose() const{ return keyMovements.stateClose; }
private:
    sf::RenderWindow* window;

    sf::Event event;

    KeyState keyMovements;
};
#include <SFML/Graphics.hpp>


/**
 * @brief 
 * stateClose - the state if the window should close, should be default to false so it does not close. Only true will window close.
 * 
 * 
 * - Might have variables representing different states in this class, allowing us to help handle how we may want to maneuver 
 */

class KeyboardInputHandler{
    struct MOVEMENTS{
        MOVEMENTS(){
            stateClose = false; // window state to close.

            // Variables indicating when we press WASD (for movements, this is just because our ideas will involve movement animations.)
            wPressed = false;
            aPressed = false;
            sPressed = false;
            dPressed = false;
        }
        
        // reset these to default values, so when we click and release it switches the values for example like ON/OFF states.
        void reset(){
            wPressed = false;
            aPressed = false;
            sPressed = false;
            dPressed = false;
        }
        
        bool stateClose; // window state to close.

        bool wPressed;
        bool aPressed;
        bool sPressed;
        bool dPressed;
    };
public:
    KeyboardInputHandler(sf::RenderWindow* _window) : window(_window){}

    ~KeyboardInputHandler(){ delete window; }

    void startEvents(){
        while(window->pollEvent(event)){
            
            // Close window when we press escape.
            if(event.key.code == sf::Keyboard::Escape) {
                keyMovements.stateClose = true;
                return;
            }

            // If we click any related key we press we switch the state to true.
            if(event.key.code == sf::Keyboard::W) keyMovements.wPressed = true;
        }
    }

    // Allow us to make function calls to make it easier to know what functions to call to allow for flexibility.
    bool forward() const{ return keyMovements.wPressed; }

    void reset(){ keyMovements.reset(); }

    bool windowShouldClose() const{ return keyMovements.stateClose; }
private:
    sf::RenderWindow* window;

    sf::Event event;

    MOVEMENTS keyMovements;
};
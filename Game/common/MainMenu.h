#pragma once
#include <iostream>
#include "GameState.h"

Class MainMenu{

/**
 * @brief 
 * 
 * Main Menu Class
 * 
 * This is our second screen after the introduction. Will call to 4(maybe 3?) other windows. 1. options, 2. game, 3. settings, 4. quit
 * 
 */

    MainMenu(unsigned int w, unsigned int h, const std::string& title, uint32_t style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings()){
        width = w;
        height = h;
        this->title = title;

    }

    private:
        unsigned int width, height;
        std::string title;
};

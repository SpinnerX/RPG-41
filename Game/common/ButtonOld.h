#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public: 
    Button() {}
    Button(sf::RenderWindow* _window, std::string title, sf::Vector2f pos, sf::Vector2f size) {}
    Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
        text.setString(t);
        // text.setColor(textColor);
        text.setFillColor(textColor);
        // text.setCharacterSize();

        button.setSize(size);
        button.setFillColor(bgColor);   
    }

    void setFont(std::string filename) {
        sf::Font font;
        if (!font.loadFromFile(filename)) return;

        text.setFont(font);
    }

    void setBackColor(sf::Color color) {
        button.setFillColor(color);
    }

    void setTextColor(sf::Color color) {
        // text.setColor(color);
        text.setFillColor(color);
    }

    void setPosition (sf::Vector2f pos) {
        button.setPosition(pos);

        float xPos = (pos.x + button.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2);
        float yPos = (pos.y + button.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2);
        text.setPosition({xPos, yPos});
    }

    void draw(sf::RenderWindow* window) {
        window->draw(button);
        window->draw(text);
    }
    //checks if mouse pos is over a button
    bool isMouseOver(sf::RenderWindow *window) {
        float mouseX = sf::Mouse::getPosition(*window).x;
        float mouseY = sf::Mouse::getPosition(*window).y;

        float btnPosX = button.getPosition().x;
        float btnPosY = button.getPosition().y;

        float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
        float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

        if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
            return true;
        } else return false;
    }
private:
    sf::RectangleShape button;
    sf::Text text;
};
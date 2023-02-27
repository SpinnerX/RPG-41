#include <SFML/Graphics.hpp>

class Button
{
public:
    // Constructor
    Button(sf::RenderWindow* window, std::string text, sf::Vector2f position, sf::Vector2f size)
    {
        m_window = window;
        m_text.setString(text);
        m_text.setPosition(position);
        m_text.setCharacterSize(20);
        m_text.setFillColor(sf::Color::Black);

        m_buttonShape.setPosition(position);
        m_buttonShape.setSize(size);
        m_buttonShape.setFillColor(sf::Color::White);
        m_buttonShape.setOutlineThickness(2.f);
        m_buttonShape.setOutlineColor(sf::Color::Black);
    }

    // Check if the button is clicked
    bool isClicked()
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window);

        if (m_buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
        {
            return sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }
urn false;
    }
        ret

    // Draw the button on the window
    void draw()
    {
        m_window->draw(m_buttonShape);
        m_window->draw(m_text);
    }

private:
    sf::RenderWindow* m_window;
    sf::Text m_text;
    sf::RectangleShape m_buttonShape;
};
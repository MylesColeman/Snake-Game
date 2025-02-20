/*
    Snake - Start Project

    This project is set up to link to SFML (a library supporting 2D graphics, sound, user input and networing)
    There is a subdirectory in the project called SFML-3.0.0 containing SFML headers and libraries
    The project settings are configured to look for these files

    SFML reference: https://www.sfml-dev.org/documentation/3.0.0/
    SFML Tutorials: https://www.sfml-dev.org/tutorials/3.0/
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1024,800 }), "GSE - E4109732");

    // Creates a circle
    sf::CircleShape circle{ 70.0f };
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(8.0f);
    circle.setOutlineColor(sf::Color::White);
    circle.setOrigin({ (35.0f), (35.0f) });
    circle.setPosition({ 140.0f, 140.0f });

    // Creates a rectangle
    sf::RectangleShape rectangle({ (75.0f), (75.0f)});
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setOutlineColor(sf::Color::Magenta);
    rectangle.setOutlineThickness(15.0f);
    rectangle.setOrigin({ (37.5f), (37.5f) });
    rectangle.setPosition({ 175.0f, 175.0f });

    // Creates a convex shape
    sf::ConvexShape convex;
    convex.setFillColor(sf::Color::Blue);
    convex.setPointCount(5);
    convex.setPoint(0, sf::Vector2f(10, 10));
    convex.setPoint(1, sf::Vector2f(200, 15));
    convex.setPoint(2, sf::Vector2f(200, 180));
    convex.setPoint(3, sf::Vector2f(105, 250));
    convex.setPoint(4, sf::Vector2f(10, 180));
    convex.setPosition({ 70.0f, 70.0f });

    // Creates a text element
    sf::Font font("data\\arial.ttf");
    sf::Text text(font);
    text.setString("Crazy Rectangle!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition({ 85.0f, 70.0f });

    // Starts a clock to track FPS
    int fps;
    sf::Clock clock = sf::Clock::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    // Loops whilst the window is open
    while (window.isOpen())
    {
        // Checks if the window has been closed
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(); // Resets the window for use

        // Adds the elements to the window
        window.draw(convex);
        window.draw(circle);
        window.draw(rectangle);
        window.draw(text);

        rectangle.rotate(sf::degrees(1.0f)); // Rotates 1 degree every frame

        // FPS calculator
        currentTime = clock.getElapsedTime(); // Checks how long the clock has been running
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // Checks how long since the last update
        previousTime = currentTime; // Sets currentTime to previousTime for the next loop

        std::string fpsString = std::to_string(fps);
        text.setString(fpsString);

        window.display();
    }
}
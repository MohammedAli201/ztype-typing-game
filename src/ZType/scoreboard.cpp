#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "scoreboard.h"
#include "scoreboard.h"
#include "GameManager.h"

scoreboard::scoreboard(size_t const &poeng) {
    sf::RenderWindow window(sf::VideoMode(500, 400), "Scoreboard", sf::Style::None);
    machine = new Machine();
    texture.loadFromFile("source/image/background.png");
    background.setTexture(texture);
    font.loadFromFile("Resource/arial.TTF");
    txt1.setFont(font);
    txt2.setFont(font);
    txt3.setFont(font);
    txt1.setPosition(100, 50);
    txt2.setPosition(40, 125);
    txt3.setPosition(325, 125);
    txt1.setFillColor(sf::Color::White);
    txt2.setFillColor(sf::Color::White);
    txt3.setFillColor(sf::Color::White);

    sf::Event event;

    std::string str = "Your final score is: ";
    txt1.setString(str += std::to_string(poeng));
    txt2.setString("Back To Menu");
   // txt3.setString("Exit game");

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseMoved) {
                if (txt2.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                    txt2.setFillColor(sf::Color::Red);
                }
                else {
                    txt2.setFillColor(sf::Color::White);
                }
                if (txt3.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                    txt3.setFillColor(sf::Color::Red);
                }
                else {
                    txt3.setFillColor(sf::Color::White);
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (txt2.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                    txt2.setStyle(sf::Text::Underlined);
                    printf("new game\n");
                    true_newgame = true;
                    window.close();

                }
                else {
                    txt2.setStyle(sf::Text::Regular);;
                }

            }
        }

        window.clear();

        window.draw(background);
        window.draw(txt1);
        window.draw(txt2);
        window.draw(txt3);
        window.display();
    }
}


scoreboard::scoreboard(size_t const &score,int const &level) {
    sf::RenderWindow window(sf::VideoMode(500, 200), "Scoreboard", sf::Style::None);

    texture.loadFromFile("source/image/background.png");
    background.setTexture(texture);
    font.loadFromFile("Resource/arial.TTF");

    txt1.setFont(font);
    txt2.setFont(font);
    txt1.setPosition(75, 35);
    txt2.setPosition(155, 110);
    txt1.setFillColor(sf::Color::White);
    txt2.setFillColor(sf::Color::White);

    std::string str1 = "Your current score is: ";
    txt1.setString(str1 += std::to_string(score));
    std::string str2 = "Next level is: ";
    txt2.setString(str2 += std::to_string(level));

    sf::Event event;

    std::string str = "Your current score is: ";
    txt1.setString(str += std::to_string(score));

    while (window.isOpen()) {
        while (window.pollEvent(event)) {

            if (clock.getElapsedTime().asMilliseconds() > 700) {
                window.close();
            }

            window.clear();

            window.draw(background);
            window.draw(txt1);
            window.draw(txt2);

            window.display();
        }
    }
}

void scoreboard::NextState(Machine &context) {

    if( true_newgame){

        context.SetRestart(restart);

    }
    else
        context.SetRunning(true_newgame);
}

scoreboard::~scoreboard() {
delete this->machine;
}






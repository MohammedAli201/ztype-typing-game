#include <sstream>
#include "SettingsWindow.h"

using namespace std;
using namespace sf;


void SettingsWindow::NextState(Machine &context) {

    sf::RenderWindow window(VideoMode(size.screenWidth, size.screenHeight), "Setting");
    texture.loadFromFile("source/image/background.png");
    background.setTexture(texture);


    if (!font.loadFromFile("Resource/Modak-Regular.ttf")) {
        cout << "Error" << endl;
    }


    sound.setFont(font);
    sound.setString("Sound");
    sound.setFillColor(sf::Color::White);
    // sound.setOutlineColor(Color::White);
    sound.setPosition(Vector2f(size.screenWidth / 3, size.screenHeight / (item + 1) * 1));
    text_option.push_back(sound);

    minus.setFont(font);
    minus.setString(" - ");
    minus.setFillColor(sf::Color::White);
    minus.setPosition(Vector2f(size.screenWidth / 3, size.screenHeight / (item + 1) * 2));
    text_option.push_back(minus);

    amount.setFont(font);
    amount.setFillColor(sf::Color::White);
    amount.setString(amoun_change);
    amount.setPosition(Vector2f((size.screenWidth / 3) + 50, size.screenHeight / (item + 1) * 2));
    text_option.push_back(amount);

    plus.setFont(font);
    plus.setString(" + ");
    plus.setFillColor(sf::Color::White);
    plus.setPosition(Vector2f((size.screenWidth / 3) + 100, size.screenHeight / (item + 1) * 2));
    text_option.push_back(plus);

    music.setFont(font);
    music.setString("Music");
    music.setFillColor(sf::Color::White);
    music.setPosition(Vector2f(size.screenWidth / 3, size.screenHeight / (item + 1) * 3));
    text_option.push_back(music);


    textureSetting.setFont(font);
    textureSetting.setString("go back to title");
    textureSetting.setFillColor(sf::Color::White);
    textureSetting.setPosition(Vector2f(size.screenWidth / 3, size.screenHeight / (item + 1) * 4));
    text_option.push_back(textureSetting);


    Event event{};

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {

                if (minus.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                    converMinus(amoun_change);
                    amount.setFont(font);
                    amount.setString(amoun_change);
                    amount.setFillColor(sf::Color::White);
                    amount.setPosition(Vector2f((size.screenWidth / 3) + 50, size.screenHeight / (item + 1) * 2));
                    printf("minys");




                }else if (plus.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                    convert(amoun_change);
                    amount.setFont(font);
                    amount.setString(amoun_change);
                    amount.setFillColor(sf::Color::White);
                    amount.setPosition(Vector2f((size.screenWidth / 3) + 50, size.screenHeight / (item + 1) * 2));
                }else if (textureSetting.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                    printf("restart\n");
                    window.close();

                    context.SetState(Machine::StateIndex ::MainMenu);

                }

            }


        }

        // window.clear(Color::Black);
        window.draw(background);

        window.draw(sound);
        window.draw(minus);
        window.draw(amount);
        window.draw(plus);
        window.draw(music);
        window.draw(textureSetting);

        window.display();

    }

}



string SettingsWindow::convert(string string2) {
    // object from the class stringstream
    stringstream geek(string2);

    // The object has the value 12345 and stream
    // it to the integer x
    int x = 0;
    geek >> x;
    if (x < 100) {
        x += 10;
        soundManager.m_Fire1Sound.setMinDistance((float)x);
        soundManager.m_Fire1Sound.setAttenuation((float)x);


    }
    std::string s = std::to_string(x);

    amoun_change = s;

    return amoun_change;
}

string SettingsWindow::converMinus(string string2) {

    //object from the class stringstream
    stringstream geek(amoun_change);

    // The object has the value 12345 and stream
    // it to the integer x
    int x = 0;
    geek >> x;
    if (x > 50) {
        x -= 10;
        soundManager.m_Fire1Sound.setMinDistance((float)x);
        soundManager.m_Fire1Sound.setAttenuation((float)x);


    } else {
        return string2;
    }
    std::string s = std::to_string(x);

    amoun_change = s;

    return amoun_change;
}
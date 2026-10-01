
#include "MenuManager.h"
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;


void MenuManager::NextState(Machine &context) {
    sf::RenderWindow window(VideoMode(size.screenWidth, size.screenHeight), "Type Shooting");

    if (!font.loadFromFile("source/image/Roboto-Black.ttf")) {
        cout << "Error" << endl;
    }

    if (!texture.loadFromFile("source/image/background.png")) {
        cout << "error" << endl;
    }
    clickedMenuIndex = 0;


    options[0].setFont(font);
    options[0].setCharacterSize(50);
    options[0].setString("New Game");
    options[0].setFillColor(Color::Red);
    options[0].setOutlineColor(Color::White);
    options[0].setPosition(Vector2f(size.screenWidth / 3, size.screenHeight / (MAX_NUMBER_OF_ITEMS + 1) *
                                                          1)); //this is a formula to position the options right at the center. the *1 implies the new game option will come before the rest of the options.

    options[1].setFont(font);
    options[1].setString("Settings");
    options[1].setFillColor(Color::White);
    options[1].setPosition(Vector2f(size.screenWidth / 3, size.screenHeight / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    options[2].setFont(font);
    options[2].setString("Levels");
    options[2].setFillColor(Color::White);
    options[2].setPosition(Vector2f(size.screenWidth / 3, size.screenHeight / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    options[3].setFont(font);
    options[3].setString("Load Your Own Text");
    options[3].setFillColor(Color::White);
    options[3].setPosition(Vector2f(size.screenWidth / 3, size.screenHeight / (MAX_NUMBER_OF_ITEMS + 1) * 4));

    options[4].setString("Exit");
    options[4].setFont(font);
    options[4].setFillColor(Color::White);
    options[4].setPosition(Vector2f(size.screenWidth / 3, size.screenHeight / (MAX_NUMBER_OF_ITEMS + 1) * 5));

    clickedMenuIndex = 0;


    Event event{};

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Up) {
                        MoveUp();

                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        MoveDown();
                    }
                    if (event.key.code == sf::Keyboard::Enter) {
                        if (clickedMenuIndex==4){
                            window.close();
                            context.SetRunning(machine_running);

                        } else if (clickedMenuIndex==3){
                            context.SetState(Machine::StateIndex::ScoreBord);

                        } else if (clickedMenuIndex==2){

                        } else if (clickedMenuIndex==1){
                            window.close();
                            context.SetState(Machine::StateIndex::Setting);

                        } else if (clickedMenuIndex==0){
                            window.close();
                            context.SetState(Machine::StateIndex::NewGame);

                        }


                    }
                    // break;
                default:
                    // Ignore the other events
                    break;
            }


        }
        background.setTexture(texture);
        window.draw(background);
        for (auto &option : options) {
            window.draw(option);
        }
        window.display();

    }




}


void MenuManager::MoveUp() {
    if (clickedMenuIndex - 1 >= 0) {
        options[clickedMenuIndex].setFillColor(Color::White);
        clickedMenuIndex--;
        options[clickedMenuIndex].setFillColor(Color::Red);
    }
}

void MenuManager::MoveDown() {
    if (clickedMenuIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        options[clickedMenuIndex].setFillColor(Color::White);
        clickedMenuIndex++;
        options[clickedMenuIndex].setFillColor(Color::Red);
    }
}





MenuManager::~MenuManager() {
}
void MenuManager::Returning(){
    if(clickedMenuIndex-1 >= 0){
        getClickedMenu() ;
    }
}





#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

#include "Levels.h"

void Levels::NextState(Machine &context) {


    if (!textureLevels.loadFromFile("source/image/image2.jpg")){
        cout<<"Error occurred\n";
    }

    spriteLevels.setTexture(textureLevels);
    while (windowLevels.isOpen()) {
        while (windowLevels.pollEvent(eventLevels)) {
            switch (eventLevels.type) {
                case sf::Event::Closed:
                    sfWindow.close();
                case sf::Event::KeyPressed:
                    if (eventLevels.key.code == sf::Keyboard::Up) {
                        printf("Hello from up levels\n");
                        //      context.SetRunning(false);
                        // Switch between two windows
                        sfWindow.close();


                    }
                    // break;
                default:
                    // Ignore the other events
                    break;
            }

            windowLevels.clear();
            windowLevels.draw(spriteLevels);
            // choices.draw(levelsWindow);
            windowLevels.display();
        }

    }

}

Levels::Levels() {
    windowLevels.create(sf::VideoMode(600, 600), "Levels  ");
//    levelsWindow.draw(windowSize,sfWindow);
    windowLevels.setVerticalSyncEnabled(true);
}

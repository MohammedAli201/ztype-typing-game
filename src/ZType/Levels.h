
#ifndef ZTYPE_LEVELS_H
#define ZTYPE_LEVELS_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Machine.h"
#include "MenuManager.h"
#include "WindowSize.h"

class Levels: public State {
    void NextState(Machine&context) override;

public:
    Levels();

    MenuManager levelsWindow;
    sf::RenderWindow sfWindow;
    WindowSize windowSize;
    sf::  RenderWindow windowLevels;


protected:
    sf::Event eventLevels;
    sf::Sprite spriteLevels;
    sf::Texture textureLevels;

};


#endif //ZTYPE_LEVELS_H

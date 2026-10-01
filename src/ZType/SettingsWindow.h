
#ifndef ZTYPE_SETTINGSWINDOW_H
#define ZTYPE_SETTINGSWINDOW_H


#include <iostream>
#include "MenuManager.h"
#include "SFML/Graphics.hpp"
#define item 7
using namespace sf;

class SettingsWindow: public  State{
public:
public:
    void NextState(Machine &context) override;
    WindowSize size;
    string convert(string s);

protected:
    Font font;
    Texture texture;
    //sf::RenderWindow window;
    Sprite background;
    //string amount={" 50 "};
    string converMinus(string s);

    Text textureSetting;
    Text minus;
    Text amount;
    Text sound;
    Text music;
    Text plus;
    vector<Text> text_option;
    string amoun_change = " 50 ";
    bool restart = false;
    SoundManager soundManager;

};


#endif //ZTYPE_SETTINGSWINDOW_H

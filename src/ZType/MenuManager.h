
#ifndef ZTYPE_MENUMANAGER_H
#define ZTYPE_MENUMANAGER_H


#include "MenuManager.h"
#include <iostream>
#include "State.h"
#include "object.h"
#include "GameManager.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Machine.h"
#define MAX_NUMBER_OF_ITEMS 5
using namespace sf;

class MenuManager: public State{

public:
    //MenuManager();
    ~MenuManager();
    void NextState(Machine&context) override ;

    void MoveUp();
    void MoveDown();
    void Returning();
    int getClickedMenu(){ return clickedMenuIndex;}
    WindowSize size;

protected:

    int clickedMenuIndex=0; //the item we selected at the current time
    Font font;
    Texture texture;
    Text options[MAX_NUMBER_OF_ITEMS];
    Sprite background;
    bool machine_running = false;

};


#endif //ZTYPE_MENUMANAGER_H

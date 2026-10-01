#ifndef ZTYPE_NEWGAME_H
#define ZTYPE_NEWGAME_H



#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "windows.h"
#include "MenuManager.h"
#include "SettingsWindow.h"
#include "MenuManager.h"
#include "WindowSize.h"
#include "winnls32.h"
#include "Machine.h"
#include "State.h"
#include "GameManager.h"

using namespace sf;
using  namespace std;
// Newgame Class send to  mainGame
class NewGame: public State {
public:
    bool restart = false;
    GameManager* game = nullptr;
    ~NewGame() override;

    void NextState(Machine&context)override ;

};


#endif //ZTYPE_NEWGAME_H

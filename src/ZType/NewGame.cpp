
#include "Machine.h"
#include "NewGame.h"
#include "MenuManager.h"


void NewGame::NextState(Machine &context) {
    game = new GameManager;
    game->runGame();
    if (!game->Game_running) {
        game->window->close();
        game->reset_game();
      context.SetRestart(restart);
    }
   context.SetState(Machine::StateIndex::MainMenu);
}

NewGame::~NewGame() {
    delete this->game;

}

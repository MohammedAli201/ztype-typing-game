
#include "MenuManager.h"
#include "Levels.h"

#include "State.h"
#include "Machine.h"
#include "NewGame.h"
#include "SettingsWindow.h"
void Machine::SetState(Machine::StateIndex state) {
    this->state = state;


}

Machine::Machine() {
    running = true;
    state = StateIndex::MainMenu;
    states.emplace(StateIndex::MainMenu, new MenuManager());
    states.emplace(StateIndex::NewGame, new NewGame());
    states.emplace(StateIndex::Setting, new SettingsWindow());


}

Machine::~Machine() {
    for (auto state: states)
        delete state.second;
    states.clear();
}

void Machine::GoNext() {

    states[state]->NextState(*this);


}

void Machine::SetRunning(bool &running) {
    this->running = running;

}

void Machine::SetRestart(bool &restart) {
this->restart= restart;
}




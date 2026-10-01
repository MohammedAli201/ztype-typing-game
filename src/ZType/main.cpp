
#include "Machine.h"

int main() {
    bool restart = false;
    Machine machine;
    // Run until the running flag is set to false
    while (machine.GetRunning()) {
        if (machine.GetRunning() && machine.GetRestart()) {
            machine.SetState(Machine::StateIndex::MainMenu);
            machine.SetRestart(restart);
        }
        machine.GoNext();
    }
    return 0;
}
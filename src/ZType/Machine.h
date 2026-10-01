
#ifndef ZTYPE_MACHINE_H
#define ZTYPE_MACHINE_H

#include <map>

class State;
class Machine {
public:
    enum class StateIndex { MainMenu,NewGame,ScoreBord,Setting };
    Machine();
    ~Machine();
    void GoNext();

    void SetState(StateIndex  state);
    bool GetRunning() const {
        return running;
    }
    bool GetRestart() const { return restart; }
    void SetRunning(bool &running);
    void  SetRestart(bool &restart);

protected:
    bool running;
    bool restart;
    StateIndex state;

protected:
    std::map<StateIndex, State*> states;

};

#endif //ZTYPE_MACHINE_H

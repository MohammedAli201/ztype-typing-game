
#ifndef ZTYPE_STATE_H
#define ZTYPE_STATE_H

class Machine ;
class State {
    public:
        State() = default;
        virtual ~State() = default;
        virtual void NextState(Machine&context) = 0;
};


#endif //ZTYPE_STATE_H

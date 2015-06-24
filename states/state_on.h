#ifndef STATE_ON_H
#define STATE_ON_H

#include <QObject>
#include "state_base.h"

class State_On : public State_Base
{
public:
    State_On(Controller *pController);
    void Move(int x, int y);
    void Off();
};

#endif // STATE_ON_H

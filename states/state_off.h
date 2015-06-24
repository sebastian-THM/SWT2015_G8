#ifndef STATE_OFF_H
#define STATE_OFF_H

#include <QObject>
#include "state_base.h"

class State_Off : public State_Base
{
public:
    State_Off(Controller *pController);
    void Move(int x, int y);
    void On();
};

#endif // STATE_OFF_H

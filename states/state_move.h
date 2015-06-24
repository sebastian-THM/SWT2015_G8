#ifndef STATE_MOVE_H
#define STATE_MOVE_H

#include <QObject>
#include "state_base.h"

class State_Move : public State_Base
{
public:
    State_Move(Controller *pController, int x, int y);
    void MoveDone();
};

#endif // STATE_MOVE_H

#ifndef STATE_CUT_H
#define STATE_CUT_H

#include <QObject>
#include "state_base.h"

class State_Cut : public State_Base
{
public:
    State_Cut(Controller *pController, int x, int y);
    void MoveDone();
};

#endif // STATE_CUT_H

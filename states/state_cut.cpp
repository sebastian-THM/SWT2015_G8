#include "state_cut.h"
#include "state_on.h"

State_Cut::State_Cut(Controller *pController, int x, int y) : State_Base(pController)
{
    emit pController -> LaserCut(x,y);
}

void State_Cut::MoveDone()
{
    StateController->Current_State = new State_On(StateController);
    delete this;
}

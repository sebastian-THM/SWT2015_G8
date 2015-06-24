#include "state_off.h"
#include "state_on.h"
#include "state_move.h"

State_Off::State_Off(Controller *pController) : State_Base(pController)
{
    StateController->LaserOff();
}

void State_Off::Move(int x, int y)
{
    StateController->Current_State = new State_Move(StateController,x,y);
    delete this;
}

void State_Off::On()
{
    StateController->Current_State = new State_On(StateController);
    delete this;
}

#include "state_move.h"
#include "state_off.h"

State_Move::State_Move(Controller *pController, int x, int y) : State_Base(pController)
{
    StateController->LaserMove(x,y);
}

void State_Move::MoveDone()
{
    StateController->Current_State = new State_Off(StateController);
    delete this;
}

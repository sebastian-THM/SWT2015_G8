#include "state_on.h"
#include "state_off.h"
#include "state_cut.h"

State_On::State_On(Controller *pController) : State_Base(pController)
{
    emit StateController->LaserOn();
}

void State_On::Move(int x, int y)
{
    StateController->Current_State = new State_Cut(StateController,x,y);
    delete this;
}

void State_On::Off()
{
    StateController->Current_State = new State_Off(StateController);
    delete this;
}

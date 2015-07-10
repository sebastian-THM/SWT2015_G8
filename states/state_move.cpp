#include "state_move.h"
#include "state_off.h"

State_Move::State_Move(Controller *pController, int x, int y) : State_Base(pController)
{
    emit StateController->LaserMove(x,y);
    connect(this,SIGNAL(destroyed(QObject*)),StateController,SLOT(inStateHasChanged()));
}

void State_Move::MoveDone()
{
    StateController->Current_State = new State_Off(StateController);
    delete this;
}

#include "state_base.h"
#include "controller.h"

State_Base::State_Base(class Controller *pController) : QObject((QObject*)pController)
{
    StateController = pController;
}


void State_Base::Move(int, int)
{
}

void State_Base::On()
{
}

void State_Base::Off()
{
}

void State_Base::MoveDone()
{
}

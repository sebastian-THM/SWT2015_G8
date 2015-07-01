#include "state_base.h"
#include "controller.h"

State_Base::State_Base(class Controller *pController) : QObject((QObject*)pController)
{
    StateController = pController;
    connect(this,SIGNAL(destroyed(QObject*)),StateController,SLOT(inStateHasChanged()));
}

void State_Base::Move(int x, int y)
{
    printf("State_Base:move(%d,%d)",x,y);
}

void State_Base::On()
{
    printf("State_Base:on()");
}

void State_Base::Off()
{
    printf("State_Base:off()");
}

void State_Base::MoveDone()
{

    printf("State_Base:position_reached()");
}

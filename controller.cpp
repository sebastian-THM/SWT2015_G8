#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    Cut_State = new State_Cut();
    Move_State = new State_Move();
    On_State = new State_On();
    Off_State = new State_Off();
    Current_State = Off_State;
}

void Controller::In_Move(char * Coords)
{

}

void Controller::In_Laser(char * State)
{

}


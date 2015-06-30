#include "controller.h"
#include "states/state_off.h"
#include <string>

Controller::Controller(QObject *parent) : QObject(parent)
{
    Current_State = new State_Off(this);
}

//Input Slots from DispatchTable
void Controller::inMove(std::string Coords)
{
    Current_State->Move(10,10);
}

void Controller::inLaser(std::string State)
{
    //Remove Spaces
    std::remove(State.begin(),State.end(),' ');
    //Remove Tabs
    std::remove(State.begin(),State.end(),'\t');
    if(State.compare("ON") == 0)
    {
        Current_State->On();
    }
    else if(State.compare("OFF") == 0)
    {
        Current_State->Off();
    }
    else
    {
        emit Error("Invalid Statecode for LASER :" + State);
    }
}

//Input from View
void Controller::inMoveDone()
{
    Current_State->MoveDone();
}

void Controller::inNewFileName(std::string Filename)
{
    //Send the Signal to the Model
    emit OpenFile(Filename);
}

void Controller::inGUIReady()
{
}

//Input from Model

void Controller::inNewFileOpend()
{
    //A new File was loaded, reset GUI and State
    emit ResetGUI();
    Current_State = new State_Off(this);
}

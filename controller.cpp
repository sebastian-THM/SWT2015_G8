#include "controller.h"
#include "states/state_off.h"
#include <string>

Controller::Controller(QObject *parent) : QObject(parent)
{
    ReadyForNextOpcode = true;
    IsFileOpened = false;
    Current_State = new State_Off(this);
    Timer = new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(onTimer()));
    Timer->start(100);
}

void Controller::onTimer()
{
    if(ReadyForNextOpcode && IsFileOpened && IsActive)
    {
        ReadyForNextOpcode = false;
        emit GetNextOpcode();
    }
}

//Input Slots from DispatchTable
void Controller::inMove(std::string Coords)
{
    std::string a;
    std::string b;
    int commapos;

    //Remove Spaces
    std::remove(Coords.begin(),Coords.end(),' ');
    //Remove Tabs
    std::remove(Coords.begin(),Coords.end(),'\t');

    commapos = Coords.find_first_of(',');

    a = Coords.substr(0,commapos);
    b = Coords.substr(commapos);

    Current_State->Move(atoi(a.c_str()),atoi(b.c_str()));
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

void Controller::inStateHasChanged()
{
    ReadyForNextOpcode = true;
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

void Controller::inStart()
{
    IsActive = true;
}

void Controller::inPause()
{
    IsActive = false;
}

//Input from Model

void Controller::inNewFileOpend()
{
    //A new File was loaded, reset GUI and State
    emit ResetGUI();
    IsFileOpened = true;
    Current_State = new State_Off(this);
    ReadyForNextOpcode = true;
    IsActive = false;
}

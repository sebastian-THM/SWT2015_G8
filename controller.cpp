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

//Signaleingänge von DispatchTable
void Controller::inMove(std::string Coords)
{
    std::string a;
    std::string b;
    int x,y;
    int commapos;
    //Leerzeichen löschen
    Coords.erase(std::remove_if(Coords.begin(), Coords.end(), ::isspace), Coords.end());

    //Kommaposition feststellen
    commapos = Coords.find_first_of(',');

    //Zahl vor und nach dem Komma Trennen
    a = Coords.substr(0,commapos);
    b = Coords.substr(commapos+1);

    //In Zahl umwandeln
    x = atoi(a.c_str());
    y = atoi(b.c_str());

    //StateMachine aufrufen
    Current_State->Move(x,y);
}

void Controller::inLaser(std::string State)
{
    //Leerzeichen entfernen
    State.erase(remove_if(State.begin(), State.end(), ::isspace), State.end());

    //Statuscode vergleichen
    if(State.compare("ON") == 0)
    {
        Current_State->On();
    }
    else if(State.compare("OFF") == 0)
    {
        Current_State->Off();
    }
}


//Wird aufgerufen wenn ein Zustandswechsel in den zustand ON oder OFF stattgefunden hat
void Controller::inStateHasChanged()
{
    ReadyForNextOpcode = true;
}


//Signaleingänge von GUI
void Controller::inMoveDone()
{
    Current_State->MoveDone();
}

void Controller::inNewFileName(std::string Filename)
{
    //Dateiname an Model weitergeben
    emit OpenFile(Filename);
}

//Aktivieren
void Controller::inStart()
{
    IsActive = true;
}

//Deaktivieren
void Controller::inPause()
{
    IsActive = false;
}

//Signaleingang vom Parser
//Datei ist Fehlerfrei und wurde Eingelesen
void Controller::inNewFileOpend()
{
    //A new File was loaded, reset GUI and State
    emit ResetGUI();
    IsFileOpened = true;
    Current_State = new State_Off(this);
    ReadyForNextOpcode = true;
    IsActive = false;
}

//Dateiname oder Dateiinhalt ist Fehlerhaft
void Controller::inFileInvalid()
{
    emit Error("Kann Datei nicht öffnen oder Datei ungültig.");
}

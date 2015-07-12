#include "controller.h"
#include "states/state_off.h"
#include <string>

Controller::Controller(QObject *parent) : QObject(parent)
{
    //Statusvariablen
    ReadyForNextOpcode = true;
    IsFileOpened = false;
    //Startzustand
    Current_State = new State_Off(this);
    //Timer erzeugen und starten
    Timer = new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(onTimer()));
    Timer->start(100);
}

void Controller::onTimer()
{
    //Auswertung der Statusvariablen und bei Bedarf anforderung des nächsten Opcodes.
    if(ReadyForNextOpcode && IsFileOpened && IsActive)
    {
        ReadyForNextOpcode = false;
        emit GetNextOpcode();
    }
}

//Signaleingänge von DispatchTable
//Der Laser soll bewegt werden ohne zu schneiden.
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

//Der Laser soll schneiden
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
//Der Laser hat sein Aktuelles ziel Erreicht.
void Controller::inMoveDone()
{
    Current_State->MoveDone();
}

//Eine Datei soll eingelesen werden
//oder der User wollte den aktuellen Vorgang abbrechen.
void Controller::inNewFileName(std::string Filename)
{
    if( Filename.compare("NOFILE")==0)
    {
      //Abruch aktuelle Datei ignorieren und die GUI zurücksetzen.
      IsFileOpened = false;
      emit ResetGUI();
    }
    else
    {
        //Dateiname an Model weitergeben
        emit OpenFile(Filename);
    }
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

//Dateiinhalt ist Fehlerhaft
void Controller::inFileInvalid()
{
    emit Error("Dateiinhalt ist fehlerhaft");
}

//Dateiname ist Fehlerhaft
void Controller::inFileNameInvalid()
{
    emit Error("Datei kann nicht geöffnet werden.");
}

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <string>
#include "states/state_base.h"
#include <QTimer>

//Controller
//Steuert den Laser

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    class State_Base *Current_State;
    //Eingänge für Aufrufe aus der Dispatch Table
    void inMove(std::string Coords);
    void inLaser(std::string State);

signals:
    //Signalausgänge zur GUI
    void LaserMove(int x, int y);
    void LaserCut(int x, int y);
    void LaserOn();
    void LaserOff();
    void ResetGUI();
    void Error(std::string ErrorMessage);
    //Signalausgänge zum Parser(Model)
    void GetNextOpcode();
    void OpenFile(std::string Filename);


public slots:
    void onTimer();
    //Signaleingänge vom der GUI
    void inMoveDone();
    void inNewFileName(std::string Filename);
    void inStart();
    void inPause();
    //Signaleingänge vom Parser
    void inNewFileOpend();
    void inFileInvalid();
    //Signaleingang von den States
    void inStateHasChanged();


private:
    QTimer *Timer;
    bool ReadyForNextOpcode;
    bool IsFileOpened;
    bool IsActive;

private slots:


};

#endif // CONTROLLER_H

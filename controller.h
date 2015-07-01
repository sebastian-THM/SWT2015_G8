#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <string>
#include "states/state_base.h"
#include <QTimer>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    class State_Base *Current_State;
    //Input from DispatchTable
    void inMove(std::string Coords);
    void inLaser(std::string State);

signals:
    //Sigals to GUI
    void LaserMove(int x, int y);
    void LaserCut(int x, int y);
    void LaserOn();
    void LaserOff();
    void ResetGUI();
    void Error(std::string ErrorMessage);
    //Signals to Model
    void GetNextOpcode();
    void OpenFile(std::string Filename);


public slots:
    void onTimer();
    //Input from View
    void inMoveDone();
    void inNewFileName(std::string Filename);
    void inStart();
    void inPause();
    //Input from Model
    void inNewFileOpend();
    //Input from States
    void inStateHasChanged();


private:
    QTimer *Timer;
    bool ReadyForNextOpcode;
    bool IsFileOpened;
    bool IsActive;

private slots:


};

#endif // CONTROLLER_H

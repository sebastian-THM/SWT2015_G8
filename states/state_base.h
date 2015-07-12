#ifndef STATE_BASE_H
#define STATE_BASE_H

#include <QObject>
#include "controller.h"


//Basisklasse für alle States
class State_Base : public QObject
{
    Q_OBJECT
public:
    State_Base(class Controller *pController);
    class Controller *StateController;
    virtual void Move(int, int);
    virtual void On();
    virtual void Off();
    virtual void MoveDone();


signals:

public slots:

private:
};

#endif // STATE_BASE_H

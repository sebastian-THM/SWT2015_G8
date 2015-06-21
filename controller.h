#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "states/state_base.h"
#include "states/state_cut.h"
#include "states/state_move.h"
#include "states/state_off.h"
#include "states/state_on.h"


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

signals:
    //Sigals to GUI
    void Laser_Move(int x, int y);
    void Laser_An();
    void Laser_Aus();


public slots:
    //Input Slots from DispatchTable
    void In_Move(char * Coords);
    void In_Laser(char * State);

private:
    State_Base *Current_State;
    State_Cut *Cut_State;
    State_Move *Move_State;
    State_Off *Off_State;
    State_On *On_State;
};

#endif // CONTROLLER_H

#ifndef STATE_BASE_H
#define STATE_BASE_H

#include <QObject>

class State_Base : public QObject
{
    Q_OBJECT
public:
    explicit State_Base(QObject *parent=0);
    void move(int x, int y);
    void on();
    void off();
    void position_reached();


signals:

public slots:

private:
};

#endif // STATE_BASE_H

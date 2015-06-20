#ifndef STATE_BASE_H
#define STATE_BASE_H

#include <QObject>

class State_Base : public QObject
{
    Q_OBJECT
public:
    explicit State_Base(QObject *parent = 0);

signals:

public slots:
};

#endif // STATE_BASE_H

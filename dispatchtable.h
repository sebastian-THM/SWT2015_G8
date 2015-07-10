#ifndef DISPATCHTABLE_H
#define DISPATCHTABLE_H

#include <QObject>
#include "controller.h"

//Ein Eintrag der DispatchTable
struct sDispatchElement
{
    std::string FunctionName;
    Controller *Object;
    void (Controller::*Function)(std::string);
};

//Als Typ festlegen
typedef struct sDispatchElement DispatchElement ;


class DispatchTable : public QObject
{
    Q_OBJECT
public:
    explicit DispatchTable(QObject *parent = 0);
    void AddFunction(std::string FunctionName,Controller *FunctionOwner ,void (Controller::*Function)(std::string));


signals:

public slots:
    void Dispatch(std::string Function, std::string Parameter);

private:
    //Liste der Hinterlegten Funktionen
    QList<DispatchElement> DispatchList;
};

#endif // DISPATCHTABLE_H

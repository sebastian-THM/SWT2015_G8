#include "dispatchtable.h"

DispatchTable::DispatchTable(QObject *parent) : QObject(parent)
{
}

//Eine Funktion soll ausgeführt werden.
void DispatchTable::Dispatch(std::string Function, std::string Parameter)
{
    DispatchElement E;
    foreach (E, DispatchList)
    {
        if(E.FunctionName.compare(Function) == 0)
        {
            ((E.Object)->*(E.Function))(Parameter);
        }
    }
}

//Eine Controller-Methode der DispatchTable hinzufügen
void DispatchTable::AddFunction(std::string FunctionName, Controller *FunctionOwner, void (Controller::*Function)(std::string))
{
    DispatchElement E;
    E.FunctionName = FunctionName;
    E.Object = FunctionOwner;
    E.Function = Function;
    DispatchList.append(E);
}

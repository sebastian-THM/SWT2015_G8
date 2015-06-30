#include "dispatchtable.h"

DispatchTable::DispatchTable(QObject *parent) : QObject(parent)
{
}

void DispatchTable::Dispatch(std::string Function, std::string Parameter)
{
    DispatchElement E;
    foreach (E, DispatchList)
    {
        if(E.FunctionName.compare(Function) == 0)
        {
            E.Function(Parameter);
        }
    }
}

void DispatchTable::AddFunction(std::string FunctionName, void (*Function)(std::string))
{
    DispatchElement E;
    E.FunctionName = FunctionName;
    E.Function = Function;
    DispatchList.append(E);
}



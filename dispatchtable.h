#ifndef DISPATCHTABLE_H
#define DISPATCHTABLE_H

#include <string>
#include <QList>

struct DispatchElement
{
    std::string FunctionName;
    void *Function(std::string);
};


class DispatchTable
{
public:
    DispatchTable();
    void AddFunction(std::string FunctionName, void *Function(std::string));

public slots:
    void Dispatch(std::string Function, std::string Parameter);

private:
    QList<DispatchElement> *DispatchList;
};

#endif // DISPATCHTABLE_H

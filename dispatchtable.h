#ifndef DISPATCHTABLE_H
#define DISPATCHTABLE_H

#include <QObject>

struct sDispatchElement
{
    std::string FunctionName;
    void (*Function)(std::string);
};

typedef struct sDispatchElement DispatchElement ;


class DispatchTable : public QObject
{
    Q_OBJECT
public:
    explicit DispatchTable(QObject *parent = 0);
    void AddFunction(std::string FunctionName, void (*Function)(std::string));


signals:

public slots:
    void Dispatch(std::string Function, std::string Parameter);

private:
    QList<DispatchElement> DispatchList;
};

#endif // DISPATCHTABLE_H

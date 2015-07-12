#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QList>
#include <string>

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);

signals:
    void FileOpened();
    void SendOpcode(std::string FunctionName, std::string Parameter);
    void FileInvalid();
    void FileNameInvalid();
public slots:
    void GetNextOpcode();
    void OpenFile(std::string Filename);
private:
    QList<std::string> OpcodeList;
};

#endif // PARSER_H

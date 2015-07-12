#include "parser.h"
#include <QFile>
#include <QDataStream>
#include <stdio.h>
#include <string>
#include <regex>


#include <iostream>
#include <string>
#include <locale>
#include <algorithm>
#include <sstream>
#include <iterator>

Parser::Parser(QObject *parent) : QObject(parent)
{

}

//Diese Funktion ist zuständig druch den
//übergebenen Dateipfad eine Datei zu öffnen und
//deren Inhalt auf ihre Korrektheit zu prüfen.
//wenn der inhalt syntaktisch korrekt ist
//werden die einzelnen informationen entnommen und in eine
//Liste OpcodeList gespeichert
void Parser::OpenFile(std::string Filename)
{

    int X;
    int i;
    std::string temp;
    std::string s;
    char text [201];


    QFile File(Filename.c_str());
    if(!File.open(QIODevice::ReadOnly))
    {
        emit FileNameInvalid();
        return;
    }

    OpcodeList.clear();

    while((X=File.readLine(text,200)) != -1)
    {
        if(text[X-1] == '\n')
        {
            text[X-1] = '\0';
        }
        if( text[X-2] == '\r')
        {
            text[X-2] = '\0';
        }

        s = std::string(text);
        if(std::regex_match(s,std::regex("^#+.*$|^MOVE [0-9]+, *[0-9]+ *$|^LASER (ON|OFF) *$|^ *$")))
        {
            memset(text,'\0',201);

            //Filter OpCode
            for(i = 0;s[i] != '\0';i++)
            {
                //Wenn der char '#'ist dann verlasse den string
                if(s[i] == '#')
                    break;
                //Wenn der nächste char ein 'L' ist dann muss es das Wort LASER sein
                //springe 4 chars weiter
                if(s[i] == 'L')
                {
                    i = i + 4;
                    OpcodeList.push_back("LASER");
                }
                //wenn der nächste char ein 'M' ist dann muss es das Wort MOVE sein
                //springe 3 chars weiter
                if(s[i] == 'M')
                {
                    i = i + 3;
                    OpcodeList.push_back("MOVE");
                }
                // wenn der nächste char ein 'O' ist dann muss es das Wort MOVE sein
                //entscheidet ob der nächste Buchstabe ein 'N' oder ein 'F'
                if(s[i] == 'O')
                {
                    //entscheide sich ob es ein 'F' ist oder nicht
                    if(s[i+1] == 'F')
                    {
                        i = i + 2;
                        OpcodeList.push_back("OFF");
                    }
                    // wenn es kein F ist kann es nur 'N' sein (also ON)
                    else
                    {
                        i = i + 1;
                        OpcodeList.push_back("ON");
                    }
                }
                //schaue nach ob eine Zahl enthalten ist
                if((s[i] == '0') || (s[i] == '1') || (s[i] == '2') || (s[i] == '3') || (s[i] == '4') || (s[i] == '5') ||
                   (s[i] == '6') || (s[i] == '7') || (s[i] == '8') || (s[i] == '9') || (s[i] == ',') || (s[i] == ' '))
                {
                    //wenn temp nicht leer ist und s ist kein ein leerzeichen
                    //dann speicher es in temp
                    if(!((temp.empty()) && (s[i] == ' ')))
                    {
                        //Speicher die zahl in temp
                        temp.push_back(s[i]);
                        if((s[i + 1] == '\0') || (s[i + 1] == '#'))
                        {
                                OpcodeList.push_back(temp);
                                temp.clear();
                                break;
                        }
                    }
                }
            }
        }
        else
        {
            //gebe das Signal FileInvalid weiter
            emit FileInvalid();
            return;
        }

    }
    //gebe das Signal FileOpend weiter
    emit FileOpened();
}

//Diese Funktion ist für die Übermittlung
//der einzelnen Opcodes zuständig
void Parser::GetNextOpcode()
{
    //variablen definition
    std::string Funktion, Parameter;

    if(!OpcodeList.empty())
    {
        //speicher die Funktion die die Variable Funktion
        Funktion = OpcodeList.first();
        //lösche das erste Elemten in der List
        OpcodeList.removeFirst();
        //speicher den Parameter in die Variable Parameter
        Parameter = OpcodeList.first();
        //lösche das erste Element in der Liste
        OpcodeList.removeFirst();
        //Sende die 2 Varablen an SendOpcode
        emit SendOpcode(Funktion, Parameter);
    }

}

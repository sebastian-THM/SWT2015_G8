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
        return;
    }

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
                //if char is '#' then quit line
                if(s[i] == '#')
                    break;
                //if char is 'L' die full word is LASER
                //steps 3 chars further
                if(s[i] == 'L')
                {
                    i = i + 4;
                    OpcodeList.push_back("LASER");
                }
                //if char is 'M' die full word is LASER
                //steps 3 chars further
                if(s[i] == 'M')
                {
                    i = i + 3;
                    OpcodeList.push_back("MOVE");
                }
                // if char is 'O' he must deside
                //if the next char is a 'F' or a 'N'
                if(s[i] == 'O')
                {
                    //desides if it is a char 'F'
                    if(s[i+1] == 'F')
                    {
                        i = i + 2;
                        OpcodeList.push_back("OFF");
                    }
                    // else it musst be a char 'N'
                    else
                    {
                        i = i + 1;
                        OpcodeList.push_back("ON");
                    }
                }
                //if the char ownes a Numer
                if((s[i] == '0') || (s[i] == '1') || (s[i] == '2') || (s[i] == '3') || (s[i] == '4') || (s[i] == '5') ||
                   (s[i] == '6') || (s[i] == '7') || (s[i] == '8') || (s[i] == '9') || (s[i] == ',') || (s[i] == ' '))
                {
                    if(!((temp.empty()) && (s[i] == ' ')))
                    {
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
            return;
        }

    }
    emit FileOpened();
}

void Parser::GetNextOpcode()
{
    std::string Funktion, Parameter;

    if(!OpcodeList.empty())
    {
        Funktion = OpcodeList.first();
        OpcodeList.removeFirst();
        Parameter = OpcodeList.first();
        OpcodeList.removeFirst();
        emit SendOpcode(Funktion, Parameter);
    }

}

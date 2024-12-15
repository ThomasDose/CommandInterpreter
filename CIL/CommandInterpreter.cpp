/***************************************************************************************************
DRS - robotics for DRS-Kit
Commandinterpreter.cpp

Links Commandinterpreter to code

(c) Thomas Dose, DRS-robotics DEC 2024

Arduino IDE 
Board Uno
****************************************************************************************************/
#include "CommandInterpreter.h"

CommandInterpreter::CommandInterpreter(){}

void CommandInterpreter::RegisterCommandEvent(void (*callback)(CommandEvent *e),char *command)
{
    Command c = {callback,command};
    list[counter++] = c;
    return;
}

void CommandInterpreter::DispathCommandEvent(char *incommingcommand, char *params)
{
    CommandEvent e = {incommingcommand,params};
    for(int i=0; i<counter;i++)
    {
        if(strcmp(incommingcommand,list[i].Name)==0)
        {
            list[i].callback(&e);
        }
    }
    return;
}

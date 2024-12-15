/*********************************************************************************************************************
DRS - robotics for DRS-Kit
Header for Commandinterpreter.cpp

Links Commandinterpreter to code

(c) Thomas Dose, DRS-robotics DEC 2024

Arduino IDE 
Board Uno
*********************************************************************************************************************/
#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H
#define MAX_COMMANDS 10                                                                   // max 10 commqands    
#include<Arduino.h>
//*******************************************************************************************************************
struct CommandEvent                                                                       // Structure of commands
{
    char *Name;                                                                           // Command Name
    char *Params;                                                                         // Parameter
};
                                                           
struct Command
{
    void (*callback)(CommandEvent *e);
    char *Name;
};
//*******************************************************************************************************************
class CommandInterpreter 
{
    private:
        Command list[MAX_COMMANDS];
        int counter =0;
    public:
        CommandInterpreter();
        void RegisterCommandEvent(void (*callback)(CommandEvent *e),char *command);
        void DispathCommandEvent(char *incommingcommand, char *params);
};
//*******************************************************************************************************************
#endif
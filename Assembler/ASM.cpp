#include "ASM.h"

int Assembler (char *bytecode, size_t *amount)
{
    struct Line* ptrstruct = Reading(amount);
    DeleteComments(ptrstruct, *amount);

    char *Command = (char*) calloc(4, sizeof(char));
    char Command_Number = -2;
    int PC = 0;
    int Param = Poison;

    for (int NumberOfLine = 0; Command_Number != 22 && NumberOfLine <*amount ; NumberOfLine++){
        ScanCommand(Command, ptrstruct, NumberOfLine);
        if (!PassTrash(Command))
            continue;
        FullBytecode(&PC, bytecode, &Command_Number, Command, NumberOfLine, ptrstruct, &Param);
    }

    free(Command);
    return PC;
}

char WhichCommand (char *Command, int amount)
{
    assert(Command!= nullptr);

  #define CMD_COMPARE(name, num) \
    { if (strcasecmp(Command, #name) == 0)\
    return num;\
    }
#define COMMANDS
#include "Commands.h"

#undef COMMANDS
#undef CMD_COMPARE

    return ErrorWhichCommand;
}


void DeleteComments (struct Line *ptrstruct, size_t amount)
{
    char *temp = nullptr;

    for (int NumberOfLine = 0; NumberOfLine < amount; NumberOfLine++) {
        if ((temp = strchr(ptrstruct[NumberOfLine].ptrbuffer, ';')) != nullptr)
            *temp = '\0';
    }
}

bool PassTrash(char *Command)
{
    return strlen(Command) != 0;
}

bool ScanCommand (char *Command, struct Line *ptrstruct, int NumberOfLine)
{
    *Command = 0;
    sscanf(ptrstruct[NumberOfLine].ptrbuffer, "%s", Command);

    return true;
}

int WhichSpec (struct Line *ptrstruct, int NumberOfLine)
{
    int Letter = 0;
    while (isalpha(ptrstruct[NumberOfLine].ptrbuffer[Letter]))
        Letter++;
    if (isnumber(ptrstruct[NumberOfLine].ptrbuffer[Letter + 1]))
        return 1;
    if (isalpha(ptrstruct[NumberOfLine].ptrbuffer[Letter + 1]) && ptrstruct[NumberOfLine].ptrbuffer[Letter] == ' ')
        return 2;
    return 3;
}

void ScanParam (int Spec, struct Line *ptrstruct, int NumberOfLine, int *Param)
{
    switch (Spec){
        case 1: {sscanf(ptrstruct[NumberOfLine].ptrbuffer, "%*s %d",        Param); break;}
        case 2: {sscanf(ptrstruct[NumberOfLine].ptrbuffer, "%*s %c", (char*)Param); break;}
        default: break;
    }

}

void FullBytecode (int *PC, char *bytecode, char *Command_Number, char *Command,
                   int NumberOfLine, struct Line *ptrstruct, int *Param)
{
    *Command_Number = WhichCommand(Command, NumberOfLine);
    bytecode[*PC] = *Command_Number;
    *PC += 1;
    bytecode[*PC] =  (char)WhichSpec (ptrstruct, NumberOfLine);
    //printf("SPEC IS %d\n", bytecode[*PC]);
    *PC += 1;
    *Param = Poison;
    ScanParam (bytecode[*PC - 1],ptrstruct, NumberOfLine, Param);
  //  printf("PARAM IS %d\n", bytecode[*PC]);
    if (*Param != Poison) {
        bytecode[*PC] = (char) *Param;
        *PC += 1;
    }
}

//printf("Command: %s, name: %s, num %d, Line`s Number: %d\n", Command, #name, num, amount);
